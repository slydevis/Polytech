/*
    Style selector
 */

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

/*
    Usefull function
 */

function addClass(elem, value) {
    if(elem.className.indexOf(value) == -1)
        elem.className = elem.className + " " + value;
}

function removeClass(elem, value) {
    elem.className = elem.className.replace(new RegExp('(?:^|\\s)'+ value +'(?!\\S)'),'');
}

function hasClass(elem, value) {
    return (' ' + elem.className + ' ').indexOf(' ' + value + ' ') > -1;
}

/* When document is ready */
window.onload = function () {
    var currentstyle = localStorage.getItem("currentstyle");

    if(currentstyle == null)
        localStorage.setItem("currentstyle", "style.css");
    else
        changeCSS(currentstyle);

    // Check if loadProgress is defined
    if(typeof (loadProgress) == "function")
        loadProgress();

    // Check if easterEgg is defined
    if(typeof (easterEgg) == "function")
        document.addEventListener("keydown", easterEgg, false);
}