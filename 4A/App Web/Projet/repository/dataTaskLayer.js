// uuid-v4 = Génére un id unique
var uuidv4 = require('uuid/v4');

// Load configuration file for database
var config = require('./../config.js').database;

var mongoose = require('mongoose');
var Schema = mongoose.Schema;

var mongo_url = "mongodb://" + config.host + ":" + config.port + "/" + config.name;

// Connect to mongoDB table
mongoose.connect(mongo_url, function (err) {
    if (err) {
        throw err;
    }
    else {
        console.log("MongoDB connected");
    }
});

// Declare schema Task
var TaskSchema = Schema({
    _id: String,
    user_id: String,
    title: String,
    completed: Boolean,
});

// Init model
var TaskModel = mongoose.model('tasks', TaskSchema);

module.exports = {
    getTaskSet: function (user, cb) {
        TaskModel.find({ user_id: user.id }, function (err, taskSet) {
            cb(taskSet);
        });
    },
    addTask: function (user, title, cb) {
        // Create a task
        var taskSamp = new TaskModel({
            _id: uuidv4(),
            user_id: user.id,
            title: title,
            completed: false,
        });

        // Save task
        taskSamp.save(function (err) {
            if (err) {
                throw err;
            }

            cb();
        });
    },
    deleteTask: function (id, cb) {
        TaskModel.deleteOne({ _id: id }, function (err) {
            if (err) {
                throw err;
            }

            cb();
        })
    },
    updateTaskCompletion: function (id, isCompleted, cb) {
        TaskModel.findOne({ _id: id }, function (err, task) {
            task.completed = isCompleted;
            task.save();
            cb(task);
        });
    },
    getTaskInfo: function (id, cb) {
        TaskModel.findOne({ _id: id }, function (err, task) {
            cb(task);
        });
    }
}