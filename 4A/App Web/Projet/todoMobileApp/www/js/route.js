app.config(function ($stateProvider) {
    // Display menu for mobile
    var appState = {
        name: 'app',
        url: '/app',
        abstract: true,
        templateUrl: 'view/menu.html',
        controller: 'appCtrl'
    };

    var homeState = {
        name: 'app.home',
        url: '',
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

    $stateProvider.state(appState);
    $stateProvider.state(homeState);
    $stateProvider.state(lampState);
    $stateProvider.state(page1State);
    $stateProvider.state(page2State);
    $stateProvider.state(todoListState);
    $stateProvider.state(compteurState);

    // $urlRouterProvider.otherwise('/app/todo');
});