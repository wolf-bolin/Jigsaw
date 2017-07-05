import os


def load_config():
    mode = os.environ.get('MODE')
    try:
        if mode == 'PRODUCTION':
            from config.production import ProductionConfig
            return ProductionConfig
        else:
            from config.development import DevelopmentConfig
            return DevelopmentConfig
    except ImportError as e:
        from config.default import Config
        return Config
