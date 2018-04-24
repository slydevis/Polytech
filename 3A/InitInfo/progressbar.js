function progressBar(bar, finalPurcent) {
    bar.style.width = 0 + "%";
    bar.innerHTML = "0%";
    var purcent = 0;
    var id = setInterval(frame, 10);

    function frame() {
        purcent+=0.5;
        bar.style.width = purcent + "%";
        bar.innerHTML = purcent.toFixed(0) + "%";
        if(purcent >= finalPurcent)
            clearInterval(id);
    }
}

function loadProgress() {
    var cpt = 0;
    var barList = document.getElementsByClassName("progress-bar");
    while(cpt < barList.length) {
        var bar = barList[cpt];
        var value = bar.getAttribute("data-value");
        if(value)
            progressBar(bar, value);
        cpt++;
    }
}