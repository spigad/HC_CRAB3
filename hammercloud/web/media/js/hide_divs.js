jQuery(function($) {

    var URL = document.location.href;
//    var parts = URL.split('/hammercloud/')

//    if (parts[1] == 'test/add/'){
    if (URL.match('/test/add/'+'$') == '/test/add/'){ 
        var allHTMLTags=document.getElementsByTagName("*");
        for (i=0; i<allHTMLTags.length; i++) {
            if (allHTMLTags[i].className=='inline-group') {
                allHTMLTags[i].style.display='none';
            }
        }

    }

});


