app.factory('userService', ['$http', '$state', '$rootScope', function ($http, $state, $rootScope) {
    var serv = {};

    serv.register = function (user, callback) {
        $http.post('/register', { user: user }).then(function (resp) {
            callback(resp.data);
        }, function (res) {
            console.log("ERROR = " + res.data.errorSet);
        });
    };

    serv.login = function (user, callback) {
        $http.post('/login', { user: user }).then(function (resp) {
            callback(resp.data);
        }, function (res) {
            console.log("ERROR = " + res.data.errorSet);
        });
    };

    serv.isLogged = function (callback) {
        if (serv.hasToken()) {
            var token = localStorage.getItem('token');
            $http.post('/isLogged', { token: token }).then(function (resp) {
                var obj = {
                    isAuth: resp.data.success,
                    user: resp.data.user
                }
                callback(obj);
            }, function (res) {
                console.log("ERROR = " + res.data.errorSet);
            });
        }
    }

    // Used in route
    serv.hasToken = function () {
        if (localStorage.getItem('token') == null) {
            return false;
        }
        else {
            return true;
        }
    }

    serv.getToken = function () {
        return localStorage.getItem('token');
    }

    serv.removeToken = function () {
        localStorage.removeItem('token');
    }

    serv.storeToken = function (token) {
        localStorage.setItem('token', token);
    }

    serv.logout = function () {
        serv.removeToken();
        $rootScope.$broadcast('userUnload');
        $state.target('app.login');
    }

    return serv;
}]);
