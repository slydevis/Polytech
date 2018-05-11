app.config(function ($stateProvider, $urlRouterProvider) {
    // Display menu for mobile
    var appState = {
        name: 'app',
        url: '',
        abstract: true,
        views: {
            'nav@': {
                templateUrl: 'view/nav.html',
                controller: 'navCtrl',
            },
            '@': {

            }
        }
    };

    var homeState = {
        name: 'app.home',
        url: '/',
        views: {
            'menuContent': {
                template: '<ion-view><ion-content><header><h1>Page d\'accueil</h1></header></ion-view></ion-content>'
            }
        }
    };

    var lampState = {
        name: 'app.lamp',
        url: '/lamp',
        views: {
            'menuContent': {
                templateUrl: 'view/lamp.html',
                controller: 'lampCtrl'
            }
        }
    };

    var page1State = {
        name: 'app.page1',
        url: '/page1',
        views: {
            'menuContent': {
                templateUrl: 'view/page1.html',
                controller: 'page1Ctrl'
            }
        }
    };

    var page2State = {
        name: 'app.page2',
        url: '/page2',
        views: {
            'menuContent': {
                template: '<ion-view><ion-content><h1 style="text-align:center">Le contenu de la page 2 </h1></ion-view><ion-content>'
            }
        }
    };

    var todoListState = {
        name: 'app.todo',
        url: '/todo',
        authenticate: true,
        views: {
            'menuContent': {
                templateUrl: 'view/todo.html',
                controller: 'todoCtrl'
            }
        }
    };

    var compteurState = {
        name: 'app.compteur',
        url: '/compteur',
        views: {
            'menuContent': {
                templateUrl: 'view/compteur.html',
                controller: 'compteurCtrl'
            }
        }
    };

    var loginState = {
        name: 'app.login',
        url: '/login',
        authenticate: false,
        views: {
            'menuContent': {
                templateUrl: 'view/login.html',
                controller: 'userCtrl'
            }
        }
    };

    var registerState = {
        name: 'app.register',
        url: '/register',
        authenticate: false,
        views: {
            'menuContent': {
                templateUrl: 'view/register.html',
                controller: 'userCtrl',
            }
        }
    };

    var logoutState = {
        name: 'app.logout',
        url: '/logout',
        authenticate: false,
        templateUrl: 'view/login.html',
        controller: 'userCtrl'
    };

    $stateProvider.state(appState);
    $stateProvider.state(homeState);
    $stateProvider.state(lampState);
    $stateProvider.state(page1State);
    $stateProvider.state(page2State);
    $stateProvider.state(todoListState);
    $stateProvider.state(compteurState);
    $stateProvider.state(loginState);
    $stateProvider.state(registerState);
    $stateProvider.state(logoutState);

    $urlRouterProvider.otherwise('/');
});

app.run(['$rootScope', 'userService', '$state', 'tradService', 'Notification', function ($rootScope, $userService, $state, $tradService, Notification) {
    $rootScope.$on('$stateChangeStart',
        function (event, toState, toParams, fromState, fromParams, options) {
            var isAuth = $userService.hasToken(); // if user get token (maybe improve security here)

            if (toState.authenticate == true) {
                if (!isAuth) {
                    Notification.info({ message: $tradService.get('user', 'MUST_LOGGED') });
                    event.preventDefault();
                    $state.go('app.login');
                }
            }

            if (toState.name == 'app.login' || toState.name == 'app.register') {
                if (isAuth) {
                    event.preventDefault();
                    $state.go('app.home');
                }
            }
            else if (toState.name == 'app.logout') {
                if (isAuth) {
                    event.preventDefault();
                    Notification.success({ message: $tradService.get('user', 'USER_LOGOUT') });
                    $userService.logout();
                }
            }
        });
}]);