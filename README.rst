Introduction
============

.. image:: https://github.com/TecnoclubCansat/2025-CanSat-Firmware/workflows/Build%20CI/badge.svg
    :target: https://github.com/TecnoclubCansat/2025-CanSat-Firmware/actions
    :alt: Build Status

.. image:: https://img.shields.io/github/release/TecnoclubCansat/2025-CanSat-Firmware.svg
    :target: https://github.com/TecnoclubCansat/2025-CanSat-Firmware/releases
    :alt: GitHub Releases

.. image:: https://img.shields.io/badge/dynamic/yaml?url=https://raw.githubusercontent.com/TecnoclubCansat/2025-CanSat-Firmware/dev/.pre-commit-config.yaml&query=$..[?(@.repo=="https://github.com/pre-commit/mirrors-clang-format")].rev&prefix=v&logo=llvm&label=clang-format&color=blue
    :target: https://clang.llvm.org/docs/ClangFormat.html
    :alt: Code Style: ClangFormat

This is the firmware used in TecnoClub Elburgo's CanSat during `CanSat <https://www.esa.int/Education/CanSat/What_is_a_CanSat>`_
2024-2025.

Downloading compiled ``.hex`` files
===================================

| :information_source: **Note**:
Pre-compiled ``.hex`` files are not available yet. Thank you for your patience.

You can find the pre-compiled ``.hex`` firmware files for Teensy 4.1 in `the Releases tab <https://github.com/TecnoclubCansat/2025-CanSat-Firmware/releases>`_
of this repository. These files are ready for use and do not require additional compilation.
The latest release can be found in `the Releases tab <https://github.com/TecnoclubCansat/2025-CanSat-Firmware/releases>`_.

``.hex`` files can be uploaded to a Teensy 4.1 board using the `Teensy Loader Application <https://www.pjrc.com/teensy/loader.html>`_.
  
Dependencies
============
The firmware depends on:

* `Adafruit ST7735 and ST7789 Library <https://github.com/adafruit/Adafruit-ST7735-Library>`_
* `BlueDot BME280 TSL2591 <https://github.com/BlueDot-Arduino/BlueDot_BME280_TSL2591>`_
* `RadioLib <https://github.com/jgromes/RadioLib>`_

`PlatformIO <https://docs.platformio.org/en/latest/librarymanager/dependencies.html#installing-dependencies>`_
automatically resolves and installs project dependencies when you build, debug, or
test a project. If you want to install project dependencies manually, please use `PlatformIO
Core (CLI) <https://docs.platformio.org/en/latest/core/index.html#piocore>`_
and the `pio pkg install <https://docs.platformio.org/en/latest/core/userguide/pkg/cmd_install.html#cmd-pkg-install>`_
command.

This repository uses some of the example code provided by the libraries listed above.


Cloning or downloading the repository
=====================================

To get started with this project, you can either clone the repository or download it as a `.zip` file:

1. **Clone the repository**:

   * Ensure that `Git <https://git-scm.com/downloads>`_
     is installed on your system.
   * Open a terminal and run the following command:

     .. code-block:: shell

         git clone https://github.com/TecnoclubCansat/2025-CanSat-Firmware.git

   * This will create a local copy of the repository, which is prefered for contributing.

2. **Download as a .zip File**:
   
   * Navigate to the **Code** button at the top of the repository's GitHub page.
   * Select **Download ZIP** to download the project files.
   * Extract the downloaded ``.zip`` file to your desired location.

Opening the project in PlatformIO
---------------------------------
1. Open `PlatformIO IDE <https://platformio.org/platformio-ide>`_.
2. In PlatformIO, go to **Open Project**.
3. Navigate to the folder where the repository was cloned or extracted and select it.
4. PlatformIO will automatically detect the ``platformio.ini`` file in the root directory and configure the project.
5. Build, upload, or test the project as needed!

Working on the repository
=========================

This repository is set up with tools that assist in development by automatically formatting code, enforcing standards,
and fixing issues where possible.

For these tools to run automatically before committing, `pre-commit <https://pre-commit.com/>`_
has to be installed. This can be done in a virtual environment in order to maintain a cleaner development setup.
Using a virtual environment isolates dependencies, ensuring they don't conflict with other projects.

The following steps explain how to install ``pre-commit`` in a Python virtual environment.

1. **Ensure Python is installed in your system.**

   You can check your version of `Python  <https://www.python.org/downloads/>`_
   with the following command:

   .. code-block:: shell 

       python --version

2. **Create a Python virtual environment.**
   
   To make a virtual environment of name ``.venv`` in the current directory, run:

   .. code-block:: shell

       python -m venv .venv

3. **Activate the virtual environment.**

   * On Windows, run:

     .. code-block:: shell

         .\.venv\Scripts\activate

   * On Linux or macOS, run:

     .. code-block:: shell

         source .venv/bin/activate

   To avoid repeating this step every time a terminal is opened in this directory,
   configure your IDE to use the ``.venv`` virtual environment as the default interpreter.
   In Visual Studio Code, this can be done by opening the command palette, typing
   ``Python: Select Interpreter`` and selecting the ``.venv`` virtual environment.

4. **Install pre-commit.**

   This can easily be achieved by executing:

   .. code-block:: shell

       pip install pre-commit

   After installing ``pre-commit``, the necessary hooks are installed on the next ``git commit``
   or the next time ``pre-commit run`` is executed.
