todoApp.controller('todoCtrl', ['$scope', 'todoService', function ($scope, $todoService) {
    $scope.tasks = [];

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
        $todoService.updateTask(task, function (res) {
            if (res) {
                $scope.refreshTaskSet();
            }
        });
    }

    $scope.removeTask = function (task) {
        $todoService.deleteTask(task, function (res) {
            if (res) {
                $scope.refreshTaskSet();
            }
        });
    }

    $scope.refreshTaskSet();
}]);