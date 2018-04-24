todoApp.config(function ($stateProvider) {
    // var loginState = {
    //     name: 'login',
    //     url: '',
    //     templateUrl: 'login.html',
    //     controller: 'userCtrl'
    // };

    // var registerState = {
    //     name: 'register',
    //     url: '/register',
    //     templateUrl: 'view/register.html',
    //     controller: 'userCtrl'
    // };

    var homeState = {
        name: 'home',
        url: '',
        template: '<header><h1>Page d\'accueil</h1></header>'
    };

    var lampState = {
        name: 'lamp',
        url: '/lamp',
        templateUrl: 'view/lamp.html',
        controller: 'lampCtrl'
    };

    var page1State = {
        name: 'page1',
        url: '/page1',
        templateUrl: 'view/page1.html',
        controller: 'page1Ctrl'
    };

    var page2State = {
        name: 'page2',
        url: '/page2',
        template: '<h3 style="text-align:center">Le contenu de la page 2 </h3>'
    };

    var todoListState = {
        name: 'todo',
        url: '/todo',
        templateUrl: 'view/todo.html',
        controller: 'todoCtrl'
    };

    var compteurState = {
        name: 'compteur',
        url: '/compteur',
        component: 'compteurComponent'
    };

    // $stateProvider.state(loginState);
    // $stateProvider.state(registerState);
    $stateProvider.state(homeState);
    $stateProvider.state(lampState);
    $stateProvider.state(page1State);
    $stateProvider.state(page2State);
    $stateProvider.state(todoListState);
    $stateProvider.state(compteurState);
});