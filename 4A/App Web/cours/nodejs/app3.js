var path = require('path');
var express = require('express');

// Needed for search method
// used to parse the request in param to get the param
var bodyParser = require('body-parser');

var app = express();
var port = 8090;

// init parser with express
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({
    extended: true
}));

// authorize access to public directory to server html, css, js
app.use(express.static(path.join(__dirname, 'public')));

app.post('/getData', function (req, res) {
    var obj = {
        success: true,
        userSet: [
            {
                firstName: 'Maurice',
                lastName: 'Topalof'
            },
            {
                firstName: 'Steeven',
                lastName: 'Seagle',
            },
            {
                firstName: 'Karine',
                lastName: 'Bolt'
            }
        ]
    }

    res.send(obj);
});

console.log('Serveur démarré port : ' + port);

app.listen(port);