todoApp.controller('compteurCtrl', ['$scope', function ($scope) {
    $scope.load = function () {
        $scope.counter = localStorage.getItem('counter');
    }

    $scope.addToCounter = function () {
        if (!$scope.counter) {
            $scope.counter = localStorage.getItem('counter');
        }

        $scope.counter++;
        localStorage.setItem('counter', $scope.counter);
    }

    $scope.load();
}]);
