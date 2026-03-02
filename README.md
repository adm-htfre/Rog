# 🤖 Rog: Raspberry Pi Robot Controller

A modular Python-based controller for driving motors via the Raspberry Pi GPIO pins. This project separates the high-level logic from the low-level hardware commands.

## 📁 Project Structure

* **`main.py`**: The central logic script.
* **`motor_driver.py`**: The hardware abstraction layer.
* **`config.py`**: Centralized configuration for GPIO pin assignments and constants.

---

## 🛠 Installation & Setup

1. **Clone the repository:**
```bash
git clone git@github.com:adm-htfre/Rog.git
cd Rog

```


2. **Set up the Virtual Environment:**
```bash
python3 -m venv env
source env/bin/activate

```


3. **Install Dependencies:**
```bash
pip install RPi.GPIO

```



---

## 🔌 Hardware Configuration

| Component | Raspberry Pi Pin (BCM) | Function |
| --- | --- | --- |
| **Motor A (Left)** | 17, 27 | Forward / Backward |
| **Motor B (Right)** | 23, 24 | Forward / Backward |
| **PWM Enable** | 18 | Speed Control |

---

## 🚀 Usage

To start the robot, ensure your virtual environment is active and run:

```bash
python3 main.py

```

### Example Snippet

```python
from motor_driver import MotorController
import config

robot = MotorController(config.LEFT_PINS, config.RIGHT_PINS)
robot.move_forward(speed=80)

```

---

## 📜 License

MIT License

---

### How to apply this change via the CLI:

Since you are getting comfortable with the CLI, here is how you update it without leaving the terminal:

1. **Open the file:** `nano README.md`
2. **Paste the text** (If you are on Windows/Mac using SSH, just right-click to paste).
3. **Save and Exit:** `Ctrl+O`, `Enter`, `Ctrl+X`.
4. **Push to GitHub:**
```bash
git add README.md
git commit -m "docs: clean up readme and remove comments"
git push

```



**Would you like me to generate the `config.py` file content to match this new structure?**
