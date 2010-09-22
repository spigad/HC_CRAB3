function test(element,val)
{
if (val == 'now'){
  var currdate = new Date();
  var hours    = currdate.getHours();
  var minutes  = currdate.getMinutes();
  var seconds  = currdate.getSeconds();
  val = hours+':'+minutes+':'+seconds;
}

if (val == '6am'){
  val = '06:00:00';
}
if (val == 'noon'){
  val = '12:00:00';
}

if (val == 'midnight'){
  val = '00:00:00';
}

  document.getElementById(element).value = val ;
}

