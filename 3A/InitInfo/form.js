/*
    Hint manager
 */
function showHint(hint, text) {
    hint.firstElementChild.innerHTML = text;
    hint.style.opacity = "0.0";
    var opacity = parseFloat(hint.style.opacity);
    var id = setInterval(frame, 50);

    function frame() {
        opacity = opacity + 0.2;

        hint.style.opacity = opacity;

        if(opacity >= 1.0) {
            clearInterval(id);
        }
    }
}

function hideHint(hint) {
    var opacity = parseFloat(hint.style.opacity);
    var id = setInterval(frame, 50);

    function frame() {
        opacity = opacity - 0.2;

        hint.style.opacity = opacity;

        if(opacity <= 0.0) {
            clearInterval(id);
        }
    }
}

function validField(field) {
    removeClass(field, "border-danger");
    removeClass(field.previousElementSibling.previousElementSibling, "error");

    addClass(field, "border-sucess");
    addClass(field, "inputValid");
    addClass(field.previousElementSibling.previousElementSibling, "correct");

    hideHint(field.previousElementSibling);
}

function errorField(field, message) {
    removeClass(field, "border-sucess");
    removeClass(field, "inputValid");
    removeClass(field.previousElementSibling.previousElementSibling, "correct");

    addClass(field, "border-danger");
    addClass(field.previousElementSibling.previousElementSibling, "error");

    showHint(field.previousElementSibling, message);
}

/*
    Check input
 */
function checkName() {
    var name = document.getElementById("name");
    if(name.value == "") {
        errorField(name, "Ce champs ne peut pas être vide");
    } else {
        validField(name);
        checkForm();
    }
}

function checkMail() {
    var email = document.getElementById("email");

    if(email.value == "") {
        errorField(email, "Ce champs ne peut pas être vide");
    }
    else {
        var regex = /^[a-z0-9._-]+@[a-z0-9._-]+\.[a-z]{2,6}$/;
        if(!regex.test(email.value)) {
            errorField(email, "Format d'email incorrect (ex : toto@toto.fr)")
        } else {
            validField(email);
            checkForm();
        }
    }
}

function checkBirthday() {
    var birthday = document.getElementById("birthday");
    if(birthday.value == "") {
        errorField(birthday, "Ce champs ne peut pas être vide");
    }
    else {
        var regex = /^[0-9]{2}\/[0-9]{2}\/[0-9]{4}$/;
        if(!regex.test(birthday.value)) {
            errorField(birthday, "Le format de la date de naissance est invalide (JJ/MM/YYYY)");
            return;
        }

        var date = birthday.value.split("/");
        var day = parseInt(date[0], 10);
        var month = parseInt(date[1], 10);
        var year = parseInt(date[2], 10);

        if(year < 1000 || year > 3000 || month == 0 || month > 12) {
            errorField(birthday, "La date est invalide");
            return;
        }

        var monthLenght = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31];

        if(year%400 == 0 || (year%100 != 0 && year%4 == 0))
            monthLenght[1] = 29;

        if(day <= 0 || day > monthLenght[month - 1]) {
            errorField(birthday, "La date est invalide");
        }
        else {
            validField(birthday);
            checkForm();
        }
    }
}

function checkMessage() {
    var message = document.getElementById("message");
    if(message.value == "") {
        errorField(message, "Le message ne peut pas être vide");
    }
    else {
        validField(message);
        checkForm();
    }
}

/*
    Check form
 */
function checkForm() {
    var submit = document.getElementById("submit");
    var message = document.getElementById("message");
    var birthday = document.getElementById("birthday");
    var email = document.getElementById("email");
    var name = document.getElementById("name");

    if(!hasClass(message, "inputValid") || !hasClass(birthday, "inputValid")
        || !hasClass(name, "inputValid") || !hasClass(email, "inputValid"))
        submit.display = true;
    else
        submit.disabled = false;
}
