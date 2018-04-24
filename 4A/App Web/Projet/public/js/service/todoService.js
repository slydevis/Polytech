todoApp.factory('todoService', ['$http', function ($http) {
    var serv = {};

    serv.addTask = function (task, callback) {
        $http.post('/addTask', { title: task }).then(function (resp) {
            callback(resp.data.success);
        }, function (res) {
            console.log("ERROR = " + res.data.errorSet);
        });
    };

    serv.getTaskSet = function (callback) {
        $http.post('/getTaskSet').then(function (resp) {
            callback(resp.data.tasks);
        }, function (res) {
            console.log("ERROR = " + res.data.errorSet);
        })
    };

    serv.deleteTask = function (task, callback) {
        $http.post('/deleteTask', task).then(function (resp) {
            callback(resp.data.success);
        }, function (res) {
            console.log("ERROR = " + res);
        });
    }

    serv.updateTask = function (task, callback) {
        $http.post('/updateTask', task).then(function (resp) {
            callback(resp.data);
        }, function (res) {
            console.log("ERROR = " + res);
        });
    }

    // serv.getTaskByUser = function ($user, callback) {
    //     $http.post('/getTasks', { user: $user }).then(function (data) {
    //         callback(data.data);
    //     }, function (res) {
    //         console.log("ERROR = " + res);
    //     });
    // }

    return serv;
}]);
