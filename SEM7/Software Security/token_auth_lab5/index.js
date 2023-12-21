const express = require('express');
const bodyParser = require('body-parser');
const path = require('path');
const { AuthenticationClient, UserInfoClient } = require('auth0');

const { auth } = require('express-oauth2-jwt-bearer');

const serverPort = 3000;

const authClient = new AuthenticationClient({
    domain: 'dev-zu5fi3y8yfa18hqy.us.auth0.com',
    clientId: 'YNf99vxIkTuiN8gFH3a3G6dcfPIb4lTB',
    clientSecret: 'wi_NbOehRSGEmCz5UcU6OwocV-w7ig7ciELHcLP3w90vovbQvQrG7DKeMkSOanCs',
});

const userInfo = new UserInfoClient({
    domain: 'dev-zu5fi3y8yfa18hqy.us.auth0.com',
});

const AUTH_HEADER = 'Authorization';

const checkJwt = auth({
    audience: 'https://dev-zu5fi3y8yfa18hqy.us.auth0.com/api/v2/',
    issuerBaseURL: `https://dev-zu5fi3y8yfa18hqy.us.auth0.com/`,
});

const app = express();
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: true }));

app.use(async (req, _, next) => {
    let user = {};
    try {
        const token = req.get(AUTH_HEADER);
        if (token) {
            const { data } = await userInfo.getUserInfo(token);
            user = data;
        }
    } catch (err) {
        console.error('Error fetching user info:', err);
    }
    req.user = user;
    next();
});


app.get('/api/profile', checkJwt, async (req, res) => {
    const auth = req.auth;
    if (auth) {
        const token = auth.token;
        const { data } = await userInfo.getUserInfo(token);
        return res.json(data);
    }
    return res.status(401).json({ 'error': 'unauthorized' });
});

app.get('/', (req, res) => {
    if (req.user.nickname) {
        return res.json(req.user);
    }
    res.sendFile(path.join(__dirname + '/index.html'));
});

// Додаткове завдання
app.post('/api/signup', async (req, res) => {
    const { login, password } = req.body;
    try {
        await authClient.database.signUp({
            email: login,
            password: password,
            connection: 'Username-Password-Authentication',
        });
        const { data } = await authClient.oauth.passwordGrant({
            username: login,
            password: password,
            scope: 'offline_access openid'
        });
        res.json(data).send();
    } catch (err) {
        res.status(401).send();
    }
});

app.post('/api/login', async (req, res) => {
    const { login, password } = req.body;
    try {
        const { data } = await authClient.oauth.passwordGrant({
            username: login,
            password,
            scope: 'offline_access openid',
            audience: 'https://dev-zu5fi3y8yfa18hqy.us.auth0.com/api/v2/',
        });
        res.json(data).send();
    } catch (err) {
        console.log(err)
        res.status(401).send();
    }
});

app.post('/api/refresh', async (req, res) => {
    const refresh_token = req.get(AUTH_HEADER);
    const { data } = await authClient.oauth.refreshTokenGrant({ refresh_token });
    res.json(data).send();
});

app.listen(serverPort, () => {
    console.log(`listening on port ${serverPort}`)
})
