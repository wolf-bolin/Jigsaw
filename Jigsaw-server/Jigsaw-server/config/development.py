from config.default import Config


class DevelopmentConfig(Config):
    # App basic config
    CONFIG_NAME = 'development'
    DEBUG = True
    SECRET_KEY = 'development key'
    SERVER_NAME = '127.0.0.1:8700'

    # Database config
    MYSQL_CONFIG = {
        'user': 'jigsaw',
        'password': 'jigsawroot',
        'host': '127.0.0.1',
        'port': '3306',
        'database': 'jigsaw',
        'raise_on_warnings': True,
    }