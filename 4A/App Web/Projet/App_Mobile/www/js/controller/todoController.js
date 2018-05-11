app.controller('todoCtrl', ['$scope', 'todoService', '$rootScope', 'Notification', 'tradService', function ($scope, $todoService, $rootScope, Notification, $tradService) {
    $scope.tasks = [];

    $scope.addTask = function () {
        if ($scope.newTask) {
            $todoService.addTask($scope.newTask.trim(), function (resp) {
                if (resp.success) {
                    $scope.refreshTaskSet();
                    $scope.newTask = ''; // Reset field
                }
                else {
                    resp.errorSet.forEach(element => {
                        Notification.error({ message: $tradService.get('todo', element) });
                    });
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
        $todoService.updateTask(task, function (res) {
            if (res.success) {
                $scope.refreshTaskSet();
            }
            else {
                resp.errorSet.forEach(element => {
                    Notification.error({ message: $tradService.get('todo', element) });
                });
            }
        });
    }

    $scope.removeTask = function (task) {
        $todoService.deleteTask(task, function (res) {
            if (res.success) {
                $scope.refreshTaskSet();
            }
            else {
                resp.errorSet.forEach(element => {
                    Notification.error({ message: $tradService.get('todo', element) });
                });
            }
        });
    }

    $scope.refreshTaskSet();
}]);