// uuid-v4 = Génére un id unique
var uuidv4 = require('uuid/v4');

var mongoose = require('mongoose');
var Schema = mongoose.Schema;

var mongo_url = "mongodb://localhost:27017/";
var mongo_database_name = "todoList";

// Connect to mongoDB table
mongoose.connect(mongo_url + mongo_database_name, function (err) {
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
    title: String,
    completed: Boolean
});

// Init model
var TaskModel = mongoose.model('tasks', TaskSchema);

module.exports = {
    getTaskSet: function (cb) {
        TaskModel.find(null, function (err, taskSet) {
            cb(taskSet);
        });
    },
    addTask: function (title, cb) {
        // Create a task
        var taskSamp = new TaskModel({
            _id: uuidv4(),
            title: title,
            completed: false
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
        TaskModel.findOne({ _id: id }, function (task) {
            cb(task);
        });
    }
}