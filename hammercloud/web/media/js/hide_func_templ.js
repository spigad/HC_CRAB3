jQuery(function($) {

  var form = document.getElementById("id_template");
  if (form && form.childNodes.length){
    var opts = form.options;
    for(i=opts.length-1;i>-1;i--){
      if(opts[i].innerHTML.indexOf('(functional)')>-1){
        form.options[i] = null; 
      };
    };
  };
});


