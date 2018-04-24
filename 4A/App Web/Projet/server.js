var path = require('path');
var express = require('express');

// Needed for search method
// used to parse the request in param to get the param
var bodyParser = require('body-parser');

// Data Task
var dataTaskLayer = require('./repository/dataTaskLayer.js');

// TODO: Add clean error

// Database management
// var mongodb = require('mongo').MongoClient; // Todo remove it

// Crypto
// var crypto = require('crypto');

// var md5sum = crypto.createHash('bcrypt');
// var s = fs.ReadStream(filename);
// s.on('data', function (d) {
//     md5sum.update(d);
// });

// s.on('end', function () {
//     var d = md5sum.digest('hex');
//     console.log(d + '  ' + filename);
// });

var app = express();
var port = 8090;

// init parser with express
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({
    extended: true
}));

// authorize access to public directory to server html, css, js
app.use(express.static(path.join(__dirname, 'public')));

/***********************************************************
 * 
 *                 UTIL FUNCTIONS
 * 
 **********************************************************/

// var mongo = {
//     insert: function (collection, obj) {
//         mongodb.connect(mongo_url, function (err, db) {
//             if (err)
//                 throw err;

//             var dbo = db.db(mongo_database_name);

//             dbo.collection(collection).insertOne(obj, function (err, res) {
//                 if (err)
//                     throw err;
//             });

//             db.close();
//         });
//     },
//     select: function (collection, query, callback) {
//         mongodb.connect(mongo_url, function (err, db) {
//             if (err)
//                 throw err;

//             var dbo = db.db(mongo_database_name);

//             dbo.collection(collection).find(query).toArray(function (err, result) {
//                 if (err)
//                     throw err;

//                 callback(result);
//             });

//             db.close();
//         });
//     },
//     count: function (collection, query = {}, callback) {
//         mongodb.connect(mongo_url, function (err, db) {
//             if (err)
//                 throw err;

//             var dbo = db.db(mongo_database_name);

//             dbo.collection(collection, query).count(function (err, count) {
//                 if (err)
//                     throw err;

//                 callback(count);
//             });

//             db.close();
//         });
//     },
//     update: function (collection, query, newvalues, callback) {
//         mongodb.connect(mongo_url, function (err, db) {
//             if (err)
//                 throw err;

//             var dbo = db.db(mongo_database_name);

//             dbo.collection(collection).updateOne(query, { $set: newvalues }, function (err, res) {
//                 if (err)
//                     throw err;

//                 callback(res);
//             });

//             db.close();
//         });
//     },
//     delete: function (collection, query, callback) {
//         mongodb.connect(mongo_url, function (err, db) {
//             if (err)
//                 throw err;

//             var dbo = db.db(mongo_database_name);

//             dbo.collection(collection).deleteOne(query, function (err, res) {
//                 if (err)
//                     throw err;

//                 callback(res);
//             });

//             db.close();
//         });
//     },
// }

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
        // TODO: Get the good user_id
        // MongoDB use asynchronous function (you need a callback in javascript)

        // mongo.select('users', { username: 'toto' }, function (user_id) {
        //     user_id = (user_id._id == null ? 0 : user_id._id);

        //     mongo.insert('task', {
        //         _id: uuidv4(),
        //         title: req.body.title,
        //         completed: false,
        //         user_id: user_id
        //     });

        //     var obj = {
        //         success: true,
        //     }

        //     console.log("OK");

        //     res.send(obj);
        // });

        dataTaskLayer.addTask(req.body.title, function () {
            var obj = {
                success: true
            }

            res.send(obj);
        });
    }
});

// TODO: Add user condition
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

    // mongo.update('task', { _id: req.body._id }, {
    //     title: req.body.title,
    //     completed: req.body.completed,
    // }, function (result) {
    //     var obj = {
    //         success: true,
    //     };

    //     res.send(obj);
    // });
});

app.post('/deleteTask', function (req, res) {
    dataTaskLayer.deleteTask(req.body._id, function (result) {
        var obj = {
            success: true,
        };

        res.send(obj);
    });

    // mongo.delete('task', { _id: req.body._id }, function (result) {
    //     var obj = {
    //         success: true,
    //     };

    //     res.send(obj);
    // });
});

app.post('/getTaskSet', function (req, res) {
    // TODO: Do this query with the good username or token or id
    dataTaskLayer.getTaskSet(function (tasks) {
        var obj = {
            success: true,
            tasks: tasks
        }

        res.send(obj);
    });

    // mongo.select('users', { username: 'toto' }, function (user_id) {
    //     user_id = (user_id._id == null ? 0 : user_id._id);

    //     mongo.select('task', { user_id: user_id }, function (tasks) {
    //         var obj = {
    //             success: true,
    //             tasks: tasks
    //         };

    //         res.send(obj);
    //     });
    // });
});

/***********************************************************
 * 
 *                      USER MANAGEMENT
 * 
 **********************************************************/

// - User
// [
//     {
//         _id: 1, // Peux être utiliser uuidv4 ?
//         username: "toto",
//         password: "hash",
//     }
// ]

// app.post('/register', function (req, res) {
//     // {
//     //     username: "toto",
//     //     password: "passwordNonHash"
//     // }

//     // TODO: Use my function
//     var url = "mongodb://localhost:27017/";
//     mongodb.connect(url, function (err, db) {
//         if (err) throw err;

//         console.log("Database created!");

//         var dbo = db.db("todoList");

//         var query = {
//             username: req.body.username
//         }

//         dbo.collection("users").find(query).toArray(function (err, result) {
//             if (err) throw err;

//             if (result.length === 0) {

//                 // TODO: Hash password
//                 var userData = {
//                     _id: result.length,
//                     username: req.body.username,
//                     password: req.body.password
//                 };

//                 dbo.collection("users").insertOne(userData, function (err, res) {
//                     if (err) throw err;
//                     console.log('User created');
//                     db.close();
//                 });
//             }
//             else {
//                 // TODO: Return an error to change username
//                 db.close();
//             }
//         });
//     });

//     var obj = {
//         success: true
//     };

//     res.send(obj);
// });

// app.post('/login', function (req, res) {
// var obj = {
//     success: true,
// };

// res.send(obj);
// });

console.log('Serveur démarré port : ' + port);

app.listen(port);