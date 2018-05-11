app.factory('todoService', ['$http', 'userService', function ($http, $userService) {
    var serv = {};

    serv.addTask = function (task, callback) {
        $http.post('http://localhost:8090/addTask', { token: $userService.getToken(), title: task }).then(function (resp) {
            callback(resp.data);
        }, function (res) {
            console.log("ERROR = " + res.data.errorSet);
        });
    };

    serv.getTaskSet = function (callback) {
        $http.post('http://localhost:8090/getTaskSet', { token: $userService.getToken() }).then(function (resp) {
            callback(resp.data.tasks);
        }, function (res) {
            console.log("ERROR = " + res.data.errorSet);
        })
    };

    serv.deleteTask = function (task, callback) {
        $http.post('http://localhost:8090/deleteTask', task).then(function (resp) {
            callback(resp.data);
        }, function (res) {
            console.log("ERROR = " + res);
        });
    }

    serv.updateTask = function (task, callback) {
        $http.post('http://localhost:8090/updateTask', task).then(function (resp) {
            callback(resp.data);
        }, function (res) {
            console.log("ERROR = " + res);
        });
    }

    return serv;
}]);
