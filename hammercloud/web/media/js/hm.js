var timeout = 500;
var closetimer = 0;
var ddmenuitem = 0;

function jsddm_open() {
    jsddm_canceltimer();
    jsddm_close();
    ddmenuitem = $(this).find('ul').css('visibility', 'visible');
}

function jsddm_close() {
    if (ddmenuitem)
        ddmenuitem.css('visibility', 'hidden');
}

function jsddm_timer() {
    closetimer = window.setTimeout(jsddm_close, timeout);
}

function jsddm_canceltimer() {
    if (closetimer) {
        window.clearTimeout(closetimer);
        closetimer = null;
    }
}

function ChangeColor(tableRow, highLight) {
    if (highLight) {
        tableRow.className = 'highlight';
    } else {
        tableRow.className = 'normal';
    }
}

function ChangeBiColor(tableRow, highLight, number) {
    if (highLight) {
        if (number % 2) {
            tableRow.className = 'highlightEven';
        } else {
            tableRow.className = 'highlightOdd';
        }
    } else {
        tableRow.className = 'normal';
    }

}

function DoNav(theUrl) {
    document.location.href = theUrl;
}

Array.prototype.remove = function(s) {
    var index = this.indexOf(s);
    if (this.indexOf(s) != -1)
        this.splice(i, 1);
}

function updateSeries(chart_id, elToHide, elToShow) {
    toHide = new Array();
    toShow = new Array();
    var i = 0;
    for (i = 0; i < elToHide.length; i++) {
        toHide.push(elToHide[i].split("_", 2)[1]);
    }
    for (i = 0; i < elToShow.length; i++) {
        toShow.push(elToShow[i].split("_", 2)[1]);
    }
    chart[chart_id].hideDataColumns(toHide);
    chart[chart_id].showDataColumns(toShow);
}

function resetForms() {
    for (i = 0; i < document.forms.length; i++) {
        document.forms[i].reset();
    }
}
