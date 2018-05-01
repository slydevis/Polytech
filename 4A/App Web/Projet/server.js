var path = require('path');
var express = require('express');

// Needed for search method
// used to parse the request in param to get the param
var bodyParser = require('body-parser');

// Data Task
var dataTaskLayer = require('./repository/dataTaskLayer.js');

// Create a ionic project command
// ionic start ionicIntro2 --type=ionic1 --cordova

// TODO: Add clean error

var app = express();
var port = 8090;

// init parser with express
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({
    extended: true
}));

// authorize access to public directory to server html, css, js
app.use(express.static(path.join(__dirname, 'public')));

// Add headers
app.use(function (req, res, next) {

    // Website you wish to allow to connect
    // res.setHeader('Access-Control-Allow-Origin', 'http://localhost:8100');
    res.setHeader('Access-Control-Allow-Origin', '*');

    // Request methods you wish to allow
    res.setHeader('Access-Control-Allow-Methods', 'GET, POST, OPTIONS, PUT, PATCH, DELETE');

    // Request headers you wish to allow
    res.setHeader('Access-Control-Allow-Headers', 'X-Requested-With,content-type');

    // Set to true if you need the website to include cookies in the requests sent
    // to the API (e.g. in case you use sessions)
    res.setHeader('Access-Control-Allow-Credentials', true);

    // Pass to next layer of middleware
    next();
});

/***********************************************************
 * 
 *                 TODO LIST MANAGEMENT
 * 
 **********************************************************/

app.post('/addTask', function (req, res) {
    if (!req.body.title) {
        res.send({
            success: false,
            errorSet: ['TASKNAME_EMPTY']
        });
    }
    else {
        dataTaskLayer.addTask(req.body.title, function () {
            var obj = {
                success: true
            }

            res.send(obj);
        });
    }
});

app.post('/readTask', function (req, res) {
    dataTaskLayer.getTaskInfo(req.body._id, function (task) {
        var obj = {
            success: true,
            task: task
        };

        res.send(obj);
    });
});

app.post('/updateTask', function (req, res) {
    dataTaskLayer.updateTaskCompletion(req.body._id, req.body.completed, function (result) {
        var obj = {
            success: true,
        };

        res.send(obj);
    });
});

app.post('/deleteTask', function (req, res) {
    dataTaskLayer.deleteTask(req.body._id, function (result) {
        var obj = {
            success: true,
        };

        res.send(obj);
    });
});

app.post('/getTaskSet', function (req, res) {
    dataTaskLayer.getTaskSet(function (tasks) {
        var obj = {
            success: true,
            tasks: tasks
        }

        res.send(obj);
    });
});

console.log('Serveur démarré port : ' + port);

app.listen(port);