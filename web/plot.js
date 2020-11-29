// global vars
local_ip = '192.168.31.80';
global_ip = '85.143.113.155';
ip = local_ip;

var TABLE = [[]];
const blackDot = '&#9899;';
const whiteDot = '&#9898;';
var sideCount = 1;
//-------------------------------------------------------

// UI functions
function getTable(data) {
    //let result = ['<table border=1 class="fit" style="width: 100%; height: 100%;">'];
    let result = ['<table border=1 class="fit">'];
    data.forEach(function(row, i, data) {
        result.push('<tr>');
        row.forEach(function(cell, j, row) {
            cellID = i + '/' + j;
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

function makeMove(x, y){
    cellID = x.toString() + '/' + y.toString();
    if (document.getElementById(cellID).innerHTML == ''){
        if (sideCount == 1){
            document.getElementById(cellID).innerHTML = blackDot;
        } else {
            document.getElementById(cellID).innerHTML = whiteDot;
        }
        sideCount = -sideCount
    } else {
        alert('ошибка на сервере');
    }
}

jQuery(function(){
    //$('TABLE').height($('TABLE').width());
    var fit_width = $('.fit td').width();
    $('.fit td').css('max-width', fit_width + 'px');
    makeTable()

    // step processing
    $(document).on('click', 'td', function(){
        if (this.innerHTML == ''){
            if (sideCount == 1){
                this.innerHTML = blackDot;
            } else {
                this.innerHTML = whiteDot;
            }
            sideCount = -sideCount
            sepIndex = this.id.indexOf("/");
            x = this.id.slice(0, sepIndex);
            y = this.id.slice(sepIndex + 1);
            processMove(x, y);
        } else {
            alert('такх, поле занято');
        }
    });
});

// process functions
function processMove(x, y){
    //alert(x + y);
    data = {
        //'requestType': 0,
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
    workingSpinnerSort(false);
    ReceivedData = JSON.parse(data);
    x = ReceivedData[0];
    y = ReceivedData[1];
    makeMove(x, y);
}


//-----------------------------------------
function workingSpinnerSort(state) {
    if (state){
        //add alert
        //var success_alert_html = jQuery('<div id="success_alert" class="alert alert-warning text_center m10" role="alert">ОБРАБОТКА</div>');
        //jQuery(".code").prepend(success_alert_html);
        //add spinner to button
        var spinner_html = '<div class="spinner-border text-light" role="status"><span class="sr-only" style="font-size: 100vw">Loading...</span></div>';
        jQuery("#Sort").text("");
        jQuery("#Sort").append(spinner_html);
    } else{
        //jQuery("#success_alert").delay(500).fadeOut(100);
        jQuery("#Sort").empty();
        jQuery("#Sort").text("Отсортировать");
    }
}

function successAlertSort(time) {
    //add alert
    // style="text-align:start; vertical-align: center; height: 2.35em;"
    jQuery("#success_alert").remove();
    var success_alert_html = jQuery('<div id="success_alert" class="text-white mx-3 mt-2"><h6>выполнено за ' + time + ' мс</h6></div>');
    jQuery("#btnGroupSort").append(success_alert_html);
    jQuery("#success_alert").delay(3000).fadeOut(500);
    setTimeout(function() {
        jQuery("#success_alert").remove();
    }, 3500);
}

function workingSpinnerCompareSort(state) {
    if (state){
        //add spinner to button
        var spinner_html = '<div class="spinner-border text-primary" role="status"><span class="sr-only" style="font-size: 100vw">Loading...</span></div>';
        jQuery("#Compare").text("");
        jQuery("#Compare").append(spinner_html);
    } else{
        //jQuery("#success_alert").delay(500).fadeOut(100);
        jQuery("#Compare").empty();
        jQuery("#Compare").text("Построить графики");
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