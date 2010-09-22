var timeout    = 500;
var closetimer = 0;
var ddmenuitem = 0;

function jsddm_open(){
	jsddm_canceltimer();
	jsddm_close();
	ddmenuitem = $(this).find('ul').css('visibility', 'visible');
}

function jsddm_close(){
	if(ddmenuitem) ddmenuitem.css('visibility', 'hidden');
}

function jsddm_timer(){
	closetimer = window.setTimeout(jsddm_close, timeout);
}

function jsddm_canceltimer(){
	if(closetimer){
		window.clearTimeout(closetimer);
		closetimer = null;
	}
}

function ChangeColor(tableRow, highLight){
	if (highLight){
		tableRow.className = 'highlight';
	}else{
		tableRow.className = 'normal';
	}
}

function ChangeBiColor(tableRow, highLight,number){
        if (highLight){
            if (number%2){ 
                tableRow.className = 'highlightEven';
            }else{
                tableRow.className = 'highlightOdd';
            }
        }else{
                tableRow.className = 'normal';
        }

}

function DoNav(theUrl){ document.location.href = theUrl; }

Array.prototype.remove=function(s){
	var index = this.indexOf(s);
	if(this.indexOf(s) != -1)this.splice(i, 1);
}

//function toggleDataSerie(checked,chart_id,column){
//	if(checked){
//		chart[chart_id].showDataColumns(column);
//		showed[chart_id].push(column);
//	}else{
//		chart[chart_id].hideDataColumns(column);
//		showed[chart_id].remove(column);
//	}
//}
//
//function showOnlyThisSerie(chart_id,column){
//	numcol = data[chart_id].getNumberOfColumns();
//	var i = 0;
//	var toHide = Array();
//	for(i=0; i<numcol; i++){
//		if(i!=column){
//			$("#checkbox_chart"+chart_id+"_serie"+i).attr('checked', false);
//			if(showed[chart_id].indexOf(i)>-1){
//				toHide.push(i);
//			}
//		}else{
//			$("#checkbox_chart"+chart_id+"_serie"+i).attr('checked', true);
//		}
//	}
//	chart[chart_id].hideDataColumns(toHide);
//	showed[chart_id] = [column];
//	chart[chart_id].showDataColumns(showed[chart_id]);
//}

function updateSeries(chart_id,elToHide,elToShow){
	toHide = new Array(); toShow = new Array();
	var i = 0;
	for(i=0; i<elToHide.length; i++){ toHide.push(elToHide[i].split("_",2)[1]); }
	for(i=0; i<elToShow.length; i++){ toShow.push(elToShow[i].split("_",2)[1]); }
	chart[chart_id].hideDataColumns(toHide);
	chart[chart_id].showDataColumns(toShow);
}

function resetForms() {
	for (i=0; i < document.forms.length; i++) { document.forms[i].reset(); }
}
