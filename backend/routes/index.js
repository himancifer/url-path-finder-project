const router = require("express").Router();

const crawlerController = require('../controllers/crawlerController');

router.post('/find-path', crawlerController.urlPathFind);

module.exports = router;