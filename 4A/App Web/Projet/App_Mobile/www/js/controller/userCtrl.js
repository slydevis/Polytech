app.controller('userCtrl', ['$scope', 'userService', '$state', '$rootScope', 'Notification', 'tradService', function ($scope, $userService, $state, $rootScope, Notification, $tradService) {
    $scope.isLogged = function () {
        $userService.isLogged(function (resp) {
            $scope.user = resp.user;
            $scope.isLogged = resp.isAuth;
            $rootScope.$broadcast('userLoad', { user: $scope.user });
        });
    }

    $scope.register = function () {
        $userService.register($scope.user, function (res) {
            if (res.success) {
                $state.go('app.login');
                Notification.success({ message: $tradService.get('user', 'USER_CREATE_SUCCESS') });
            }
            else {
                res.errorSet.forEach(element => {
                    Notification.error({ message: $tradService.get('user', element) });
                });
            }
        });
    }

    $scope.login = function () {
        $userService.login($scope.user, function (res) {
            if (res.success == true) {
                $scope.user = res.user;

                // Update navbar
                $rootScope.$broadcast('userLoad', { user: $scope.user, isLogged: true });

                // Store login token
                $userService.storeToken(res.token);

                $state.go('app.todo');
                Notification.success({ message: $tradService.get('user', 'LOGIN_SUCCESS') });
            }
            else {
                res.errorSet.forEach(element => {
                    Notification.error({ message: $tradService.get('user', element) });
                });
            }
        });
    }

    $scope.isLogged();
}]);