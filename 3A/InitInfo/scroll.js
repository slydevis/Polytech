/*
 Scroll to anchor functions
 */

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