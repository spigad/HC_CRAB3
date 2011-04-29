jQuery(function($) {

  var hosts      = document.getElementById('getTestHosts_for_test-group');
  var backends   = document.getElementById('getTestBackends_for_test-group');
  var clouds     = document.getElementById('getTestClouds_for_test-group');
  var sites      = document.getElementById('getTestSites_for_test-group');
  var dspatterns = document.getElementById('getTestDspatterns_for_test-group');

  if (hosts && hosts.childNodes.length){
    var hths = hosts.getElementsByTagName("th");
    hths[1].innerHTML = "Delete ALL ?";
    hths[1].onclick = function(){
      var htds = hosts.getElementsByTagName("td");
      for (h=0;h<htds.length;h++){
        if(htds[h].className.indexOf('delete')>-1 && htds[h].childNodes.length>0){
          htds[h].childNodes[0].checked = true;
        };
      };
    };
  };

  if (backends && backends.childNodes.length){
    var bths = backends.getElementsByTagName("th");
    bths[6].innerHTML = "Delete ALL ?";
    bths[6].onclick = function(){
      var btds = backends.getElementsByTagName("td");
      for (b=0;b<btds.length;b++){
        if(btds[b].className.indexOf('delete')>-1 && btds[b].childNodes.length>0){
          btds[b].childNodes[0].checked = true;
        };
      };
    };
  };

  if (clouds && clouds.childNodes.length){
    var cths = clouds.getElementsByTagName("th");
    cths[6].innerHTML = "Delete ALL ?";
    cths[6].onclick = function(){
      var ctds = clouds.getElementsByTagName("td");
      for (c=0;c<ctds.length;c++){
        if(ctds[c].className.indexOf('delete')>-1 && ctds[c].childNodes.length>0){
          ctds[c].childNodes[0].checked = true;
        };
      };
    };
  };

  if (sites && sites.childNodes.length){
    var sths = sites.getElementsByTagName("th");
    sths[6].innerHTML = "Delete ALL ?";
    sths[6].onclick = function(){
      var stds = sites.getElementsByTagName("td");
      for (s=0;s<stds.length;s++){
        if(stds[s].className.indexOf('delete')>-1 && stds[s].childNodes.length>0){
          stds[s].childNodes[0].checked = true;
        };
      };
    };
  };

  if (dspatterns && dspatterns.childNodes.length){
    var dths = dspatterns.getElementsByTagName("th");
    dths[1].innerHTML = "Delete ALL ?";
    dths[1].onclick = function(){
      var dtds = dspatterns.getElementsByTagName("td");
      for (d=0;d<dtds.length;d++){
        if(dtds[d].className.indexOf('delete')>-1 && dtds[d].childNodes.length>0){
          dtds[d].childNodes[0].checked = true;
        };
      };
    };
  };

});

