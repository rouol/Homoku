// global vars
local_ip = '192.168.31.80';
global_ip = '85.143.113.155';
ip = local_ip;

var TABLE = [[]];
const blackDot = '&#9899;';
const whiteDot = '&#9898;';
var gameStart = false;
var sideCount = 1;
var player = 1;
var lastCellID = 0;
var lastStatus = 0;
var winner = 0;
var gameID = 0;
//-------------------------------------------------------

// UI functions
function getTable(data) {
    //let result = ['<table border=1 class="fit" style="width: 100%; height: 100%;">'];
    let result = ['<table border=1 class="fit">'];
    data.forEach(function(row, i, data) {
        result.push('<tr>');
        row.forEach(function(cell, j, row) {
            cellID = i + 'X' + j;
            result.push(`<td id="${cellID}">${cell}</td>`);
        });
        result.push('</tr>');
    });
    /*
    for(let row of data) {
        result.push('<tr>');
        for(let cell of row){
            result.push(`<td id="` +  + `">${cell}</td>`);
        }
        result.push('</tr>');
    }
    */
    result.push('</table>');
    return result.join('\n');
}

function makeTable(){
    TABLE = Array(19).fill().map(()=>Array(19).fill(''))
    htmlTABLE = getTable(TABLE)
    jQuery("#TABLE").append(htmlTABLE);
}

function clearTable(){
    jQuery("#TABLE").empty();
    makeTable();
}

function makeMove(x, y){
    cellID = x.toString() + 'X' + y.toString();
    if (document.getElementById(cellID).innerHTML == ''){
        if (sideCount == 1){
            document.getElementById(cellID).innerHTML = blackDot;
        } else {
            document.getElementById(cellID).innerHTML = whiteDot;
        }
        //jQuery('#' + lastCellID).removeClass('bg-danger');
        //jQuery('#' + lastCellID).removeClass('rounded');
        jQuery('#' + cellID).addClass('bg-danger');
        jQuery('#' + cellID).addClass('rounded-lg');
        //jQuery('#' + cellID).delay(3000).removeClass('bg-danger');
        //jQuery('#' + cellID).delay(3000).removeClass('rounded');
        sideCount = -sideCount
        lastCellID = cellID;
    } else {
        alert('ошибка на сервере');
    }
}

jQuery(function(){
    //$('TABLE').height($('TABLE').width());
    var fit_width = $('.fit td').width();
    $('.fit td').css('max-width', fit_width + 'px');
    makeTable()

    jQuery('#startGame').click(function(){
        clearTable()
        startGame(player);
    });
    jQuery('#black').click(function(){
        player = 1;
        jQuery('#playerDropdown').html(jQuery('#black').html());
    });
    jQuery('#white').click(function(){
        player = -1;
        jQuery('#playerDropdown').html(jQuery('#white').html());
    });

    // step processing
    $(document).on('click', 'td', function(){
        if (gameStart == true){
            if (this.innerHTML == ''){
                jQuery('#' + lastCellID).removeClass('bg-danger');
                jQuery('#' + lastCellID).removeClass('rounded-lg');
                if (sideCount == 1){
                    this.innerHTML = blackDot;
                } else {
                    this.innerHTML = whiteDot;
                }
                sideCount = -sideCount
                sepIndex = this.id.indexOf("X");
                x = this.id.slice(0, sepIndex);
                y = this.id.slice(sepIndex + 1);
                processMove(x, y);
            } else {
                alert('такх, поле занято');
            }
        } else alert('начните игру');
        
    });
});

// process functions
function startGame(player){
    data = {
        'requestType': 0,
        'player': player
    }
    jQuery.post(
        'http://' + ip + ':5100',
        data,
        successStart
    );
}

function successStart(data){
    ReceivedData = JSON.parse(data);
    sideCount = 1;
    if (player == -1){
        x = ReceivedData[0];
        y = ReceivedData[1];
        gameID = ReceivedData[2];
        makeMove(x, y);
    } else {gameID = ReceivedData;}
    
    if (lastStatus == 0) jQuery('#maininput').removeClass('bg-dark');
    else if (lastStatus == 1) jQuery('#maininput').removeClass('bg-success');
    else if (lastStatus == 2) jQuery('#maininput').removeClass('bg-danger');
    jQuery('#maininput').addClass('bg-primary');
    gameStart = true;
}

function processMove(x, y){
    data = {
        'requestType': 1,
        'id': gameID,
        'x': x,
        'y': y
    }
    jQuery.post(
        'http://' + ip + ':5100',
        data,
        successMove
    );
}

function successMove(data){
    ReceivedData = JSON.parse(data);
    if (ReceivedData.length == 3) {
        winner = ReceivedData[2];
    }
    if (ReceivedData[0] >= 0) {
        x = ReceivedData[0];
        y = ReceivedData[1];
        makeMove(x, y);
    } else {alert('сдаюсь...');}
    if (winner == 1) {
        // win of black
        alert('черные победили');
    } else if (winner == -1) {
        // win of white
        alert('белые победили');
    }
    if (winner != 0) {
        if (winner == player){
            jQuery('#maininput').removeClass('bg-primary');
            jQuery('#maininput').addClass('bg-success');
            lastStatus = 1;
        } else {
            jQuery('#maininput').removeClass('bg-primary');
            jQuery('#maininput').addClass('bg-danger');
            lastStatus = 2;
        }
        gameStart = false;
        winner = 0;
        sideCount = player;
    }
    
}

// Utility functions
function removeItemOnce(arr, value) {
    var index = arr.indexOf(value);
    if (index > -1) {
        arr.splice(index, 1);
    }
    return arr;
}
  
function removeItemAll(arr, value) {
var i = 0;
while (i < arr.length) {
    if (arr[i] === value) {
    arr.splice(i, 1);
    } else {
    ++i;
    }
}
return arr;
}