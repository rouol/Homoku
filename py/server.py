from http.server import BaseHTTPRequestHandler, HTTPServer
import logging
from urllib.parse import parse_qs
import json
import random
from subprocess import Popen, PIPE
import os

processMap = {}


def generateProcessID():
    new_id = random.randint(0, 100000)
    while new_id in processMap:
        new_id = random.randint(0, 100000)
    return new_id


def startGame(data):
    global processMap
    cpp_process = Popen(['..\cpp\homoku.exe'], shell=True, stdout=PIPE, stdin=PIPE)
    process_id = generateProcessID()

    # send player
    player = int(data['player'][0])
    value = str(player) + '\n'
    value = bytes(value, 'UTF-8')  # Needed in Python 3.
    cpp_process.stdin.write(value)
    cpp_process.stdin.flush()
    if player == -1:
        answer = list(map(int, cpp_process.stdout.readline().strip().decode('utf-8').split()))
        answer.append(process_id)
    else:
        answer = process_id
    processMap[process_id] = [cpp_process, player]
    return answer


def makeMove(data):
    global processMap
    process_id = int(data['id'][0])
    cpp_process = processMap[process_id][0]
    # send x, y
    value = data['x'][0] + ' ' + data['y'][0] + '\n'
    value = bytes(value, 'UTF-8')  # Needed in Python 3.
    cpp_process.stdin.write(value)
    cpp_process.stdin.flush()

    answer = list(map(int, cpp_process.stdout.readline().strip().decode('utf-8').split()))
    if len(answer) == 3:
        Popen.kill(cpp_process)
        del processMap[process_id]
    if len(answer) == 0:
        player = processMap[process_id][1]
        answer = [-1, -1, player]
    return answer


class S(BaseHTTPRequestHandler):
    def _set_response(self):
        self.send_response(200)
        self.send_header('Content-type', 'text/html')
        self.send_header("Access-Control-Allow-Origin", "*")
        self.end_headers()
        # print('out', self.headers)

    def do_GET(self):
        logging.info("GET request,\nPath: %s\nHeaders:\n%s\n", str(self.path), str(self.headers))
        self._set_response()
        self.wfile.write("GET request for {}".format(self.path).encode('utf-8'))

    def do_POST(self):
        content_length = int(self.headers['Content-Length'])  # <--- Gets the size of data
        post_data = self.rfile.read(content_length)  # <--- Gets the data itself
        # print(post_data)
        # print('in', self.headers)
        # logging.info("POST request,\nPath: %s\nHeaders:\n%s\n\nBody:\n%s\n",
        #             str(self.path), str(self.headers), post_data.decode('utf-8'))
        data = parse_qs(post_data.decode('utf-8'))
        # print(data)

        # print(post_data.decode('utf-8'))

        self._set_response()
        answer = 0
        process_id = 'start'
        if data['requestType'][0] == '0':
            answer = startGame(data)
        elif data['requestType'][0] == '1':
            process_id = int(data['id'][0])
            answer = makeMove(data)
        print(process_id, answer)
        json_string = json.dumps(answer)
        self.wfile.write(json_string.encode(encoding='utf_8'))


def run(server_class=HTTPServer, handler_class=S, port=5100):
    # run C++ session
    # global cppProcess
    # cpp_process = Popen(['..\cpp\homoku.exe'], shell=True, stdout=PIPE, stdin=PIPE)

    logging.basicConfig(level=logging.INFO)
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    logging.info('Starting httpd...\n')
    try:
        httpd.serve_forever()
    except KeyboardInterrupt:
        pass
    httpd.server_close()
    logging.info('Stopping httpd...\n')


if __name__ == '__main__':
    from sys import argv

    if len(argv) == 2:
        # int(argv[1])
        run(port=5100)
    else:
        run()
