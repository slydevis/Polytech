app.controller('navCtrl', ['$scope', '$rootScope', 'userService', function ($scope, $rootScope, $userService) {
    $scope.user = {};

    $scope.isLogged = false;

    $rootScope.$on('userLoad', function (event, opt) {
        $scope.user = opt.user;
        $scope.isLogged = opt.isLogged;
    });

    $rootScope.$on('userUnload', function (event, opt) {
        $scope.user = {};
        $scope.isLogged = false;
    });

    // Trigger when scope is loaded
    $scope.$on('$viewContentLoaded', function (event) {
        $('.sidenav').sidenav(); // Enable sideNav from materialize.js
        $(".dropdown-trigger").dropdown(); // Enable Dropdown

        $userService.isLogged(function (resp) {
            $rootScope.$broadcast('userLoad', { user: resp.user, isLogged: resp.isAuth })
        });
    });
}]);