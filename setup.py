import setuptools

setuptools.setup(
    name='llmbroker',
    version='0.1.0',
    packages=setuptools.find_packages(),
    install_requires=[
        "pytorch==2.2",
        "pandas==2.2.1",
        "networkx==3.2.1"
    ],
    url='https://github.com/jialuechen/llmbroker',
    license='MIT',
    author='Jialue Chen',
    author_email='jialuechen@outlook.com',
    description='LLM Based Quantitaitve Trading Python Library'
)
