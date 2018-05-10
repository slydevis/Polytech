app.config(function ($stateProvider, $urlRouterProvider) {
    var rootState = {
        name: 'app',
        abstract: true,
        views: {
            'nav@': {
                templateUrl: 'view/nav.html',
                controller: 'navCtrl',
            },
            '@': {

            }
        }
    }

    var homeState = {
        name: 'app.home',
        url: '/',
        template: '<header><h1>Page d\'accueil</h1></header>'
    };

    var lampState = {
        name: 'app.lamp',
        url: '/lamp',
        templateUrl: 'view/lamp.html',
        controller: 'lampCtrl'
    };

    var page1State = {
        name: 'app.page1',
        url: '/page1',
        templateUrl: 'view/page1.html',
        controller: 'page1Ctrl'
    };

    var page2State = {
        name: 'app.page2',
        url: '/page2',
        template: '<h1 style="text-align:center">Le contenu de la page 2 </h1>'
    };

    var todoListState = {
        name: 'app.todo',
        url: '/todo',
        authenticate: true,
        templateUrl: 'view/todo.html',
        controller: 'todoCtrl',
    };

    var compteurState = {
        name: 'app.compteur',
        url: '/compteur',
        templateUrl: 'view/compteur.html',
        controller: 'compteurCtrl'
    };

    var loginState = {
        name: 'app.login',
        url: '/login',
        authenticate: false,
        templateUrl: 'view/login.html',
        controller: 'userCtrl'
    };

    var registerState = {
        name: 'app.register',
        url: '/register',
        authenticate: false,
        templateUrl: 'view/register.html',
        controller: 'userCtrl',
    };

    var logoutState = {
        name: 'app.logout',
        url: '/logout',
        authenticate: false,
        templateUrl: 'view/login.html',
        controller: 'userCtrl',
        resolve: {
            logout: function (userService, Notification, tradService) {
                Notification.success({ message: tradService.get('user', 'USER_LOGOUT') });
                return userService.logout();
            }
        }
    }

    $stateProvider.state(rootState);
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


app.run(['$rootScope', '$transitions', 'userService', 'Notification', 'tradService', function ($rootScope, $transitions, $userService, Notification, $tradService) {
    // Redirect to login if user is not logged
    $transitions.onBefore({}, function (transition) {
        var state = transition.$to();

        var isAuth = $userService.hasToken(); // if user get token (maybe improve security here)

        if (state.authenticate == true) {
            if (!isAuth) {
                Notification.info({ message: $tradService.get('user', 'MUST_LOGGED') });
                return transition.router.stateService.target('app.login');
            }
        }

        if (state.name == 'app.login' || state.name == 'app.register') {
            if (isAuth) {
                return transition.router.stateService.target('app.home');
            }
        }
        else if (state.name == 'app.logout') {
            if (!isAuth) {
                return transition.router.stateService.target('app.login');
            }
        }
    });
}]);