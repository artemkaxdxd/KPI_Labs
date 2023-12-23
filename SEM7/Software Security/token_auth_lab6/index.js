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

app.get('/api/redirect', (_, res) => { // Редірект з параметрами
    return res.redirect(301,
        `https://dev-zu5fi3y8yfa18hqy.us.auth0.com/authorize
        ?client_id=YNf99vxIkTuiN8gFH3a3G6dcfPIb4lTB
        &redirect_uri=http://localhost:3000/
        &response_type=code
        &response_mode=query
        &scope=offline_access+openid+profile
        &audience=https://dev-zu5fi3y8yfa18hqy.us.auth0.com/api/v2/
        &prompt=login
    `);
})

// Додаткове завдання - обробка редіректа
app.get('/api/callback', async (req, res) => {
    const code = req.query['code'];
    if (code) {
        const data = await authClient.oauth.authorizationCodeGrant({
            code,
            redirect_uri: 'http://localhost:3000/',
            grant_type: 'authorization_code'
        });
        return res.json(data.data);
    }
    return res.status(403).json({ error: 'Forbidden' });
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

app.get('/', (_, res) => {
    res.sendFile(path.join(__dirname + '/index.html'));
});


app.post('/api/refresh', async (req, res) => {
    const refresh_token = req.get(AUTH_HEADER);
    const { data } = await authClient.oauth.refreshTokenGrant({ refresh_token });
    res.json(data).send();
});

app.listen(serverPort, () => {
    console.log(`listening on port ${serverPort}`)
})
