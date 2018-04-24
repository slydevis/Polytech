todoApp.controller('todoCtrl', ['$scope', 'todoService', function ($scope, $todoService) {
    // TODO: If user is not logged => GOTO login
    $scope.tasks = [];

    // TODO: Have the good user id or by username or by token
    $scope.addTask = function () {
        if ($scope.newTask) {
            $todoService.addTask($scope.newTask.trim(), function (resp) {
                if (resp) {
                    $scope.refreshTaskSet();
                    $scope.newTask = ''; // Reset field
                }
            })
        }
    }

    $scope.refreshTaskSet = function () {
        $todoService.getTaskSet(function (taskSet) {
            $scope.tasks = taskSet;
        });
    }

    $scope.changeCompletion = function (task) {
        // localStorageService.saveTask($scope.tasks);
        $todoService.updateTask(task, function (res) {
            if (res) {
                $scope.refreshTaskSet();
            }
        });
    }

    $scope.removeTask = function (task) {
        // localStorageService.saveTask($scope.tasks);
        $todoService.deleteTask(task, function (res) {
            if (res) {
                $scope.refreshTaskSet();
            }
        });
    }

    $scope.refreshTaskSet();
}]);

// TODO: Code this part
// todoApp.controller('userCtrl', ['$scope', "$http", "$state", function ($scope, $http, $state) {
//     // TODO: If user is already logged => GOTO todo list
//     $scope.register = function () {
//         console.log("Register");

//         var userData = {
//             username: $scope.user.username,
//             password: $scope.user.password
//         };

//         $http.post('/register', userData).then(function (data) {
//             console.log("User created");
//         }, function (res) {
//             console.log(res);
//         });
//     }

//     $scope.login = function () {
//         console.log("Login");

//         // TODO: Tempory redirect to todoList


//         // var userData = {
//         // username: $scope.user.username,
//         // password: $scope.user.password,
//         // }

//         // $http.post('/login', userData).then(function (data) {
//         // console.log('LOGGED USER');
//         // TODO: Redirect to todoList
//         // TODO: Log user
//         // }, function (res) {
//         // console.log(res);
//         // });

//     }

//     $state.go('todoList');
// }]);

// Code prof :
// $score.taskSet = [];

// $scope.refreshTaskSet = function () {
//     $todoService.getTaskSet(function (taskSet) {
//         $scope.taskSet = taskSet;
//     });
// }

// todoApp.factory('localStorageService', function ($http) {
//     var serv = {};

//     // Get tasks from local storage
//     serv.getSavedTask = function () {
//         var tasks = localStorage.getItem('tasks');

//         if (tasks) {
//             return JSON.parse(tasks);
//         }
//         else {
//             tasks = [];
//             $http.post('/getTasks').then(function (data) {
//                 data.data.tasks.forEach(e => {
//                     tasks.push(e);
//                 });

//                 serv.saveTask(tasks);
//             }, function (res) {
//                 console.log(res);
//             });
//         }

//         return tasks;
//     }

//     // Save tasks to the local storage
//     serv.saveTask = function (tasks) {
//         localStorage.setItem('tasks', angular.toJson((tasks)));
//         $http.post('/saveTasks', tasks).then(function (data) {
//             console.log("Save OK = " + data.data);
//         }, function (res) {
//             console.log("Error : Problem to save tasks to the server");
//         });
//     }

//     return serv;
// });
