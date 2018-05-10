var path = require('path');
var express = require('express');

// Needed for search method
// used to parse the request in param to get the param
var bodyParser = require('body-parser');

// JWT Token
var jwt = require('jsonwebtoken');

// Config variables
var config = require('./config.js');

// Data Task
var dataTaskLayer = require('./repository/dataTaskLayer.js');

// Data User
var dataUserLayer = require('./repository/dataUserLayer.js');

// Create a ionic project command
// ionic start todoAppMobile --type=ionic1 --cordova

var app = express();

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
    var errorSet = [];

    if (!req.body.title) {
        errorSet.push('TASKNAME_EMPTY');
    }

    if (!req.body.token) {
        errorSet.push('NO_TOKEN');
    }

    if (errorSet.length == 0) {
        jwt.verify(req.body.token, config.secret, function (err, decoded) {
            if (err) {
                return res.json({
                    success: false,
                    errorSet: ['INVALID_TOKEN']
                });
            }
            else {
                dataTaskLayer.addTask(decoded, req.body.title, function () {
                    var obj = {
                        success: true
                    }

                    res.send(obj);
                });
            }
        });
    }
    else {
        res.send({
            success: false,
            errorSet: errorSet,
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
    if (!req.body.token) {
        res.send({
            success: false,
            errorSet: ['NO_TOKEN']
        });
    }
    else {
        jwt.verify(req.body.token, config.secret, function (err, decoded) {
            if (err) {
                return res.json({
                    success: false,
                    errorSet: ['INVALID_TOKEN']
                });
            }
            else {
                dataTaskLayer.getTaskSet(decoded, function (tasks) {
                    var obj = {
                        success: true,
                        tasks: tasks
                    }

                    res.send(obj);
                });
            }
        });
    }
});

/***********************************************************
 * 
 *                 USER MANAGEMENT
 * 
 **********************************************************/
app.post('/register', function (req, res) {
    var user = req.body.user;

    if (!user) {
        res.send({
            success: false,
            errorSet: ['USER_EMPTY']
        });
    }
    else {
        var errorSet = [];

        if (!user.username) {
            errorSet.push('USERNAME_EMPTY');
        }

        if (!user.password) {
            errorSet.push('PASSWORD_EMPTY');
        }
        else if (!user.confirmPassword) {
            errorSet.push('PASSWORD_CONFIRM_EMPTY');
        }
        else if (user.password != user.confirmPassword) {
            errorSet.push('PASSWORD_DIFFERENT');
        }

        if (!user.email) {
            errorSet.push('EMAIL_EMPTY');
        }
        else {
            // Check if email is valid
            var reg = /^(([^<>()\[\]\\.,;:\s@"]+(\.[^<>()\[\]\\.,;:\s@"]+)*)|(".+"))@((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\])|(([a-zA-Z\-0-9]+\.)+[a-zA-Z]{2,}))$/;

            if (!reg.test(user.email.toLowerCase())) {
                errorSet.set('INVALID_EMAIL');
            }
        }

        if (errorSet.length == 0) {
            dataUserLayer.getUser(user, function (result) {
                if (result.length > 0) {
                    res.send({
                        success: false,
                        errorSet: ['USER_ALREADY_EXIST']
                    });
                }
                else {
                    dataUserLayer.register(user, function () {
                        var obj = {
                            success: true,
                        }

                        res.send(obj);
                    });
                }
            });
        }
        else {
            res.send({
                success: false,
                errorSet: errorSet
            });
        }
    }
});

app.post('/login', function (req, res) {
    var user = req.body.user;

    dataUserLayer.login(user, function (result) {
        if (!result) {
            var obj = {
                success: false,
                errorSet: ['LOGIN_FAIL'],
            }
        }
        else {
            const payload = {
                id: result._id,
                user: {
                    username: result.username
                }
            };

            var token = jwt.sign(payload, config.secret, {
                expiresIn: "1 days" // Expires in 24 hours
            });

            var obj = {
                success: true,
                token: token,
                user: payload.user,
            }
        }

        res.send(obj);
    })
});

app.post('/isLogged', function (req, res) {
    if (req.body.token) {
        jwt.verify(req.body.token, config.secret, function (err, decoded) {
            if (err) {
                res.json({
                    success: false,
                    errorSet: ['INVALID_TOKEN']
                });
            }
            else {
                var obj = {
                    success: true,
                    user: decoded.user
                }

                res.send(obj);
            }
        });
    }
    else {
        var obj = {
            success: false,
            errorSet: ['NOT_LOGGED']
        }
    }
});

console.log('Serveur démarré port : ' + config.port);

app.listen(config.port);