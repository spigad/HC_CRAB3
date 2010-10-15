
function zoomInOut(me,items,metric){
  if (me.className == 'in'){
    generateTable(true,items,metric);
    me.setAttribute("class","out");
  }else{
    generateTable(false,items,metric);
    me.setAttribute("class","in");
  };

  // Set everything to 'on'
  bars = ['leftbar','rightbar','footerbar'];
  for (b=0;b<bars.length;b++){

    var bar = document.getElementById(bars[b]);

    if (bars[b] == 'footerbar'){
      var labels = bar.getElementsByTagName('td');
    }else{
      var labels = bar.getElementsByTagName('li');
    };//end if-else

    for (l=0;l<labels.length;l++){
      if (labels[l].className.indexOf('off') > -1){
        labels[l].setAttribute("class",labels[l].className.replace('off','on'));
      };
    };
  };//enf for(b=0
};

function toggleDisplay(me){
  if (me.childNodes[1].style.display=='block'){
    me.childNodes[1].style.display='none';
  }else{
    var map = document.getElementById('map');
    var tds = map.getElementsByTagName('td');

    for (i=0;i<tds.length;i++){
      tds[i].childNodes[1].style.display = 'none';
    };
    me.childNodes[1].style.display='block';
  };
};

// items = [['name','percentage','rightcol','leftcol']]
function generateTable(enlarge,items,metric){

  toWrite = new Array(50);
  toCount = new Array(50);

  var TABLE_WIDTH = 15;

  for (i=0;i<toWrite.length;i++){
    toWrite[i] = new Array(TABLE_WIDTH);
    toCount[i] = new Array(TABLE_WIDTH);
  };

  if (enlarge){
    length = [3,3,3,6,6,9];
  }else{
    length = [1,1,1,3,3,4];
  };
  height = [1,1,1,1,2,3];

  colors  = ['ongrey','ongreen','onyellow','onred','onred','onred'];

  var myTable = document.getElementById("map");
  while(myTable.hasChildNodes()){
    myTable.removeChild(myTable.firstChild);
  };

  for (s=0;s<items.length;s++){
    if (items[s][1] < 0.0){
      lhc = 0;
    }else if(items[s][1] < 0.5){
      lhc = 5;
    }else if(items[s][1] < 0.7){
      lhc = 4;
    }else if(items[s][1] < 0.8){
      lhc = 3;
    }else if(items[s][1] < 0.95){
      lhc = 2;
    }else{
      lhc = 1;
    };

    lock = -1;
    y = -1;
    x = 0;

    while (lock != 0){

      y += 1;

      for (i=0;i<TABLE_WIDTH;i++){

        dance:

        if (i+length[lhc] < TABLE_WIDTH + 1) {

          for (h=0;h<height[lhc];h++){
            for (l=0;l<length[lhc];l++){
              if (toCount[y+h][i+l] == 1){
                break dance;
              };//end if
            };//end for l
          };//end for h

          if (lock == -1){
            x = i;
            lock = 0;
            break;
          };

        };//end if < 13
      };//end for i

    };//end while


    for (j=y;j<y+height[lhc];j++){
      for (i=x;i<x+length[lhc];i++){
        toCount[j][i] = 1;
      };//end for i
    };//end for j
    toWrite[y][x] = [length[lhc],height[lhc],colors[lhc],items[s]];

  };

  for (y=0;y<toWrite.length;y++){

    var row = document.createElement("tr");

    for (x=0;x<toWrite[y].length;x++){

      var cell = document.createElement("td");
      if (toWrite[y][x]){

        var message = ' ';
        if (toWrite[y][x][2].indexOf('red') > -1 || enlarge){
          var message = toWrite[y][x][3][0];
        }

        customMsg = 'No test yesterday.';
        if (toWrite[y][x][2] != 'ongrey'){
          customMsg ="<p>"+metric+" "+toWrite[y][x][3][1]+"%</p>";
        }

        cell.innerHTML = message+"<span class='map_legend'><h3>"+toWrite[y][x][3][0]+"</h3>"+customMsg+"</span>";
        cell.setAttribute("rowspan",toWrite[y][x][1]);
        cell.setAttribute("colspan",toWrite[y][x][0]);
        cell.setAttribute("class",toWrite[y][x][3][2]+' '+ toWrite[y][x][3][3]+' '+toWrite[y][x][2]);
        cell.setAttribute("onclick","DoNav('"+toWrite[y][x][3][4]+"');")
//onclick="DoNav('{% url test-view app test.id %}');"
        if (enlarge){
          cell.style.width = '120px';
        };
        row.appendChild(cell);
      };
    };

    myTable.appendChild(row);

  };
};

function hideShow(me,bar_name,klass){

  next = ''

  if (me.className.indexOf('on') > -1){
    me.setAttribute("class",me.className.replace('on','off'));
    next = 'off';
  }else{
    me.setAttribute("class",me.className.replace('off','on'));
    next = 'on';
  };

  var map = document.getElementById('map');
  var tds = map.getElementsByTagName('td');

  lock = false;

  var stillOff = new Array()
  if(next=='on'){

    bars = ['leftbar','rightbar','footerbar'];
    for (b=0;b<bars.length;b++){
      if (bars[b] != bar_name) {

        var bar = document.getElementById(bars[b]);

        if (bars[b] == 'footerbar'){
          var labels = bar.getElementsByTagName('td');
          for (l=0;l<labels.length;l++){
            if (labels[l].className.indexOf('off') > -1){
              stillOff.push([labels[l].className]);
            };
          };
        }else{
          var labels = bar.getElementsByTagName('li');
          for (l=0;l<labels.length;l++){
            if (labels[l].className.indexOf('off') > -1){
              name = labels[l].childNodes[0].data;
              stillOff.push(name);
            };
          };//end for
        };//end if-else
      };//end bars[b]
    };//enf for(b=0
  };//end next=on

  for (i=0;i<tds.length;i++){
    if (tds[i].className.indexOf(klass) > -1){ // || klass == 'ALL'){
      if (next=='off'){
        tds[i].setAttribute("class",tds[i].className.replace('on','off'));
      }else{
        tds_lock = true;
        for(s=0;s<stillOff.length;s++){
          if (tds[i].className.indexOf(stillOff[s]) > -1){
            tds_lock = false;
              break;
          };
        };
        if (tds_lock){
          tds[i].setAttribute("class",tds[i].className.replace('off','on'));
        };//enf id tds_lock
      };//end else
    };//end if (tds[i]
  };//enf for
};

