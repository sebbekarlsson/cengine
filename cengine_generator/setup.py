from setuptools import setup, find_packages


setup(
    name='cengine_generator',
    version='1.0.0',
    install_requires=[
    ],
    packages=find_packages(),
    entry_points={
        'console_scripts': [
            'ceg = cengine_generator.bin:run'
        ]
    }
)
