app.factory('todoService', ['$http', 'userService', function ($http, $userService) {
    var serv = {};

    serv.addTask = function (task, callback) {
        $http.post('/addTask', { token: $userService.getToken(), title: task }).then(function (resp) {
            callback(resp.data);
        }, function (res) {
            console.log("ERROR = " + res.data.errorSet);
        });
    };

    serv.getTaskSet = function (callback) {
        $http.post('/getTaskSet', { token: $userService.getToken() }).then(function (resp) {
            callback(resp.data.tasks);
        }, function (res) {
            console.log("ERROR = " + res.data.errorSet);
        })
    };

    serv.deleteTask = function (task, callback) {
        $http.post('/deleteTask', task).then(function (resp) {
            callback(resp.data);
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

    return serv;
}]);
