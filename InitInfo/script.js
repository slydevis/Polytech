// TODO : Coder proprement + commenter
// TODO : Refaire une indentation propre

// TODO : Enlever cette fonction trop complexe pour une personne qui a jamais de javascript normalement
function $(x) {return document.getElementById(x);}

/*
    Fonction Utile
 */

function addClass(elem, value) {
    if(elem.className.indexOf(value) == -1)
        elem.className = elem.className + " " + value;
}

function removeClass(elem, value) {
    elem.className = elem.className.replace(new RegExp('(?:^|\\s)'+ value +'(?!\\S)'),'');
}

function clearAllInterval() {
  for (var i = 1; i < 99999; i++)
    window.clearInterval(i);
}

var isBoxOpened = false;

function themeManager() {
    var currentTheme = localStorage.getItem("currentstyle");
    if(currentTheme == "style.css")
        changeCSS("dark.css");
    else
        changeCSS("style.css");
}

/* This function change the CSS file for the current page */
function changeCSS(cssFile) {
    var currentTheme = cssFile;
    document.getElementsByTagName("link")
                          .item(1).setAttribute("href", cssFile);
    localStorage.setItem("currentstyle", currentTheme);  
}

function infoBoxTest() {
    addClass(document.getElementById("infoAlert"), "alert-success");

    if(isBoxOpened === true)
    infoBoxFadeOut();
  else
    infoBoxFadeIn();
}

function infoBoxFadeOut() {
  var infoBox = document.getElementById("infoAlert");

  /* Default value to hide block in transition */
  var height = parseInt(infoBox.style.height);
  var id = setInterval(frame, 7);

  function frame() {
    height--;
    
    infoBox.style.height = height + "px";
    
    if(height == 30) {
      infoBox.style.color = "transparent";
      infoBox.style.padding = 0;
    }
  
    if(height === 0) {
        infoBox.style.display = "none";
        clearInterval(id);
    }
  }
  
  isBoxOpened = false;
}

function infoBoxFadeIn() {
  var infoBox = document.getElementById("infoAlert");

  /* Default value to hide block in transition */
  var height = 0;
  var padding = 0;

  infoBox.style.display = "block";
  infoBox.style.border = "1px solid transparent";
  infoBox.style.height = "0" + "px";
  infoBox.style.border = "0" + "px";
  infoBox.style.color = "transparent";
  infoBox.style.padding = "0" + "px";

  var id = setInterval(frame, 7);

  function frame() {
    height++;
    padding++;
    
    infoBox.style.height = height + "px";
    
    if(padding <= 15) {
      infoBox.style.paddingTop = padding + "px";
      infoBox.style.paddingRight = padding + "px";
      infoBox.style.paddingLeft = padding + "px";
    }
    
    if(height == 30)
      infoBox.style.color = "#3c763d";
  
    if(height == 50) {
        infoBox.style.paddingBottom = "15px";   
        clearInterval(id);
    }
  }
  
  isBoxOpened = true;
}

/* When document is ready */
window.onload = function ()
{
    document.addEventListener("keydown", easterEgg, false);
    
    var currentstyle = localStorage.getItem("currentstyle");

    if(currentstyle == null)
      localStorage.setItem("currentstyle", "style.css");
    else
      changeCSS(currentstyle);


    // TODO : Check if this code is needed 
    var selector, elems, makeActive;

    selector = '#nav li';

    elems = document.querySelectorAll(selector);

    makeActive = function () {
        for (var i = 0; i < elems.length; i++)
            elems[i].classList.remove('active');

        this.classList.add('active');
    };

    for (var i = 0; i < elems.length; i++)
        elems[i].addEventListener('mousedown', makeActive);
}

function playSound() {
    $('music').innerHTML = '<object type="audio/mpeg" width="0" height="0" data="nyancatSong.mp3"><param name="filename" value="nyancatSong.mp3" />' +
        '<param name="autostart" value="true" />' +
        '<param name="loop" value="true" /></object>';
}

function stopSound() {
  $('music').innerHTML = '';
}

function freeNyanCatLeft(nyan) {
  var width = window.innerWidth
      || document.documentElement.clientWidth
      || document.body.clientWidth;

  nyan.style.left = "-1000px";
  nyan.style.top = "100px";
  nyan.style.display = "inline";
  nyan.style.marginLeft = "-350px";
  nyan.style.webkitTransform = 'rotate('+0+'deg)'; 
  nyan.style.mozTransform    = 'rotate('+0+'deg)'; 
  nyan.style.msTransform     = 'rotate('+0+'deg)'; 
  nyan.style.oTransform      = 'rotate('+0+'deg)'; 
  nyan.style.transform       = 'rotate('+0+'deg)';  
  
  var id = setInterval(frame, 1);
  var left = -1000;
  
  function frame() {
    left = left + 3;
    
    nyan.style.left = left + "px";
    
    if(left >= width + 350) {
        nyan.style.left = -1000 + "px";
        left = -1000;
        clearInterval(id);
        freeNyanCat();
    }
  }
}

function freeNyanCatDiagonal(nyan) {

  var up = window.innerHeight
|| document.documentElement.clientHeight
|| document.body.clientHeight;
  nyan.style.left = "-800px";
  nyan.style.top = up + 100 + "px";
  nyan.style.display = "inline";
  nyan.style.marginLeft = "auto";
  nyan.style.webkitTransform = 'rotate('+320+'deg)'; 
  nyan.style.mozTransform    = 'rotate('+320+'deg)'; 
  nyan.style.msTransform     = 'rotate('+320+'deg)'; 
  nyan.style.oTransform      = 'rotate('+320+'deg)'; 
  nyan.style.transform       = 'rotate('+320+'deg)';  
  
  var id = setInterval(frame, 1);
  var left = -200;
  var top = up + 100;
  
  function frame() {
    left = left + 3;
    top = top - 3;
    
    nyan.style.left = left + "px";
    nyan.style.top = top + "px";
    
    if(top <= -400) {
        nyan.style.left = -200 + "px";
        nyan.style.top = up + 100;
        
        left = -200;
        top = up + 100;
        clearInterval(id);
        freeNyanCat();
    }
  }
}

function freeNyanCatUp(nyan) {

   var height = window.innerHeight
        || document.documentElement.clientHeight
        || document.body.clientHeight;

  nyan.style.display = "inline";
  nyan.style.left = "50%";
  nyan.style.marginLeft = "-350px";
  nyan.style.top = height + 1000 + "px";

  nyan.style.webkitTransform = 'rotate('+270+'deg)';
  nyan.style.mozTransform    = 'rotate('+270+'deg)'; 
  nyan.style.msTransform     = 'rotate('+270+'deg)'; 
  nyan.style.oTransform      = 'rotate('+270+'deg)'; 
  nyan.style.transform       = 'rotate('+270+'deg)';  
  
  var id = setInterval(frame, 1);
  var top = height + 1000;
  
  function frame() {
    top = top - 4;
    
    nyan.style.top = top + "px";

    if(top <= -500) {
        nyan.style.top = height + 1000 + "px";
        top = height + 1000;
        clearInterval(id);
        freeNyanCat();
    }
  }
  
}

function freeNyanCat() {
  var nyan = document.getElementById("nyanCat");
  var rand  = Math.floor(Math.random() * 3) + 1;
  
  switch(rand) {
    case 1:
      freeNyanCatLeft(nyan);
      break;
    case 2:
       freeNyanCatDiagonal(nyan);
      break;
    case 3:
      freeNyanCatUp(nyan);
      break;
  }
}

function catchNyanCat() {
  var nyan = document.getElementById("nyanCat");
  nyan.style.display = "none";
  clearAllInterval();
}

function freeTroll() {
  var trol = document.getElementById("trol");
  var height = window.innerHeight
|| document.documentElement.clientHeight
|| document.body.clientHeight;
  localStorage.setItem("backgroundValue", document.body.style.background);
  trol.style.left = "0px";
  trol.style.top = height + 340 + "px";
  trol.style.display = "inline";
  
  var deg = 360;
  trol.style.webkitTransform = 'rotate('+deg+'deg)'; 
  trol.style.mozTransform    = 'rotate('+deg+'deg)'; 
  trol.style.msTransform     = 'rotate('+deg+'deg)'; 
  trol.style.oTransform      = 'rotate('+deg+'deg)'; 
  trol.style.transform       = 'rotate('+deg+'deg)';
  trol.style.left = 0 + "px";

  var id = setInterval(frame, 10);
  var id2 = setInterval(frame2, 200);
  var heightbuff = height + 340;
  var width = window.innerWidth
    || document.documentElement.clientWidth
    || document.body.clientWidth;
  var left = parseInt(trol.style.left, 10);
  var sens = true;
  var epic = false;
  
  function frame() {
      
    if(heightbuff <= height - 340)
    {
      deg = deg - 1;
    
      trol.style.webkitTransform = 'rotate('+deg+'deg)'; 
      trol.style.mozTransform    = 'rotate('+deg+'deg)'; 
      trol.style.msTransform     = 'rotate('+deg+'deg)'; 
      trol.style.oTransform      = 'rotate('+deg+'deg)'; 
      trol.style.transform       = 'rotate('+deg+'deg)'; 
    
      if(deg == 0)
        deg = 360;
      
      if(sens == true || left == 0)  {
          left = left + 3;
          
          if(left >= width - 320)
            sens = false;
      }
      
      if(left >= width - 320 || sens == false) {
        left = left - 3;
        
        if(left == 0)
          sens = true;
      }
      
      trol.style.left = left + "px";
    }
    else {
      heightbuff = heightbuff - 6;
      trol.style.top = heightbuff + "px";
    }
  }
  
  function frame2() {
    epic = !epic;
    if(epic == true) {
      document.body.style.background = "#237691";
    }
    else
      document.body.style.background = "#E3DA5D";
  }
}

function catchTroll() {
  var troll = document.getElementById("trol");
  troll.style.display = "none";
  document.body.style.background = localStorage.getItem("backgroundValue");
  clearAllInterval();
}

function easterEgg(e) {
  if(e.keyCode == 84) { // Touche T
    if($('music').childNodes.length > 0) {
      stopSound();
      catchNyanCat();
      catchTroll();
    } else { 
      playSound();
      freeNyanCat();
      freeTroll();
    }
  }
}
function getPosition(element) {
  var curleft = curtop = 0;
  var obj = element;
  if (obj.offsetParent) {
    do {
      curleft += obj.offsetLeft;
      curtop += obj.offsetTop;
      obj = obj.offsetParent
    } while (obj.offsetParent);
  }
  return { x: curleft, y: curtop };
}

function scrollToAnchor(obj) {
  var id = obj.getAttribute("href");
  id = id.replace("#", "");
  console.log(id);
  var elem = document.getElementById(id);
  var pos = getPosition(elem);
  var y = window.pageYOffset;

  if(pos.y < y) {
    var id = setInterval(frame, 10);
    function frame() {
        if(pos.y >= y) {
            clearInterval(id);
        }

        if(y > pos.y)
            y-=5;
        window.scrollTo(0, y);
    }
  }

  if(pos.y > y) {
    var id = setInterval(frame2, 10);

    function frame2() {
      if(pos.y <= y) {
        clearInterval(id);
      }
        if(y < pos.y)
            y+=5;

      window.scrollTo(0, y);
    }
  }

    return false;
}