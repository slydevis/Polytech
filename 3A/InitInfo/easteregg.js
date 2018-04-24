var frameNyan;
var frameTroll;
var frameBack;

function easterEgg(e) {
    if(e.keyCode == 84) { // Touche T
        if(document.getElementById('music').childNodes.length > 0) {
            stopSound();
            catchNyanCat();
            catchTroll();
            cleanBackground();
        } else {
            playSound();
            freeNyanCat();
            freeTroll();
            epicBackground();
        }
    }
}

/*
    Background easter
 */
function epicBackground() {
    localStorage.setItem("backgroundValue", document.body.style.background);
    var epic = false;
    frameBack = setInterval(frame, 200);

    function frame() {
        epic = !epic;
        if(epic == true) {
            document.body.style.background = "#237691";
        }
        else
            document.body.style.background = "#E3DA5D";
    }
}

function cleanBackground() {
    document.body.style.background = localStorage.getItem("backgroundValue");
    clearInterval(frameBack);
}

/*
    Sound easter
 */
function playSound() {
    document.getElementById("music").innerHTML = '<object type="audio/mpeg" width="0" height="0" data="nyancatSong.mp3"><param name="filename" value="nyancatSong.mp3" />' +
        '<param name="autostart" value="true" />' +
        '<param name="loop" value="true" /></object>';
}

function stopSound() {
    document.getElementById('music').innerHTML = '';
}

/*
    Nyan Cat easter
 */
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

    frameNyan = setInterval(frame, 1);
    var left = -1000;

    function frame() {
        left = left + 3;

        nyan.style.left = left + "px";

        if(left >= width + 350) {
            nyan.style.left = -1000 + "px";
            left = -1000;
            clearInterval(frameNyan);
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

    frameNyan = setInterval(frame, 1);
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
            clearInterval(frameNyan);
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

    frameNyan = setInterval(frame, 1);
    var top = height + 1000;

    function frame() {
        top = top - 4;

        nyan.style.top = top + "px";

        if(top <= -500) {
            nyan.style.top = height + 1000 + "px";
            top = height + 1000;
            clearInterval(frameNyan);
            freeNyanCat();
        }
    }
}

function catchNyanCat() {
    var nyan = document.getElementById("nyanCat");
    nyan.style.display = "none";
    clearInterval(frameNyan);
}

/*
    Troll easter
 */
function freeTroll() {
    var trol = document.getElementById("trol");
    var height = window.innerHeight
        || document.documentElement.clientHeight
        || document.body.clientHeight;
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

    frameTroll = setInterval(frame, 10);
    var heightbuff = height + 340;
    var width = window.innerWidth
        || document.documentElement.clientWidth
        || document.body.clientWidth;
    var left = parseInt(trol.style.left, 10);
    var sens = true;

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
}

function catchTroll() {
    var troll = document.getElementById("trol");
    troll.style.display = "none";
    clearInterval(frameTroll);
}
