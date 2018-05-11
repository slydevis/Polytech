// uuid-v4 = Génére un id unique
var uuidv4 = require('uuid/v4');

// Load configuration file for database
var config = require('./../config.js').database;

var mongoose = require('mongoose');
var Schema = mongoose.Schema;

var crypto = require('crypto'); // sha1

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
var UserSchema = Schema({
    _id: String,
    username: String,
    email: String,
    password: String,
});

// Init model
var UserModel = mongoose.model('users', UserSchema);

// Used to hash passwords
function sha1(data) {
    var generator = crypto.createHash('sha1');
    generator.update(data);
    return generator.digest('hex');
}

module.exports = {
    getUser: function (user, cb) {
        UserModel.find({
            $or: [
                { username: user.username },
                { email: user.email }
            ]
        }, function (err, user) {
            if (err) {
                throw err;
            }

            cb(user);
        });
    },
    register: function (user, cb) {
        var newUser = new UserModel({
            _id: uuidv4(),
            username: user.username,
            email: user.email,
            password: sha1(user.password),
        });

        newUser.save(function (err) {
            if (err) {
                throw err;
            }

            cb();
        });
    },
    login: function (user, cb) {
        UserModel.findOne({
            $or: [
                { username: user.login, password: sha1(user.password) },
                { email: user.login, password: sha1(user.password) }
            ]
        }
            , function (err, userObj) {
                if (err) {
                    throw err;
                }

                if (userObj) {
                    userObj.save();
                }

                cb(userObj);
            });
    }
}