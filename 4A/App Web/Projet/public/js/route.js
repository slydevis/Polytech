todoApp.config(function ($stateProvider) {
    var loginState = {
        name: 'login',
        url: '',
        templateUrl: 'login.html',
        controller: 'userCtrl'
    };

    var registerState = {
        name: 'register',
        url: '/register',
        templateUrl: 'register.html',
        controller: 'userCtrl'
    };

    var todoList = {
        name: 'todoList',
        url: '/tasks',
        templateUrl: 'todo.html',
        controller: 'todoCtrl'
    };

    $stateProvider.state(loginState);
    $stateProvider.state(registerState);
    $stateProvider.state(todoList);
});