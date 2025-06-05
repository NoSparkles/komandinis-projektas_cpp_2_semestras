# Finance Manager App

## Team: *Unhandled Exception*

### Authors
| Name               | Role                                      |
|--------------------|-------------------------------------------|
| **Robert Šatkevič** | Backend Developer, Documentation Writer, Tester, Quality Assurance   |
| **Aurimas Vižinis** | Frontend Developer, Documentation Writer, Presenter, Communication Specialist  |
| **Dominykas Pavlavičius** | Programmer, Tester |

---

## Description
The Finance Manager App is a comprehensive tool designed to help users manage their finances effectively. It allows users to track income and expenses, apply filters, and visualize data through tables and pie charts. The app also supports exporting filtered data for further analysis.

---

## Features Overview

### Use Case Diagram
![Use Case Diagram](./image1.png)

- **User Interactions:**
  - The diagram illustrates how the user interacts with the system, including choosing between income or expense views, adding new entries, filtering data by value, type, or date, and saving/exporting data as tables or pie charts.

---

## Analysis

### Data Flow Overview

#### Flowchart Diagram
![Flowchart](./image2.png)

- This diagram shows the flow of data within the application:
  1. **User Input** is validated.
  2. Valid data is saved to a **Storage File**.
  3. Filters are applied to view data as a **Table** or **Pie Chart**.
  4. Data can be exported or saved.
---

### Application Flow

#### Component Interaction Diagram
![Application Logic](./image3.png)

- This diagram represents the interaction between components:
  - The **Application** communicates with **View Controllers** (Main and Add Entry).
  - **View Controllers** interact with the **Data Manager**, which handles data storage and retrieval from the **Storage File**.

---

### Class diagram
![Class Diagram](./class_diagram.png)

## Technology Stack

| Layer         | Technology Used      |
|---------------|-----------------------|
| **Frontend**  | C++, QT |
| **Backend**   | C++    |
| **Storage**   | Local File System           |
| **Visualization** | Pie Charts, Tables |
| **Tools**     | QT Creator, Smartdraw, Git/GitHub |
---
## Work Contribution Log (LFF Format)

### Aurimas Vižinis
- **2025-03-23** — *11:30–13:30* — **120 min**  
  **Activity:** Programavimas  
  **Comments:** Frontend dalies programavimas  

- **2025-03-26** — *11:00–13:00* — **120 min**  
  **Activity:** Planavimas, PSP veikla  
  **Comments:** UML diagramos, pildoma laiko fiksavimo lentelė  

- **2025-04-05** — *18:00–19:10* — **70 min**  
  **Activity:** Atsiskaitymas  
  **Comments:** Klaidų taisymas: readme, UML diagramų taisymas

- **2025-04-25** — *15:30—16:30* — **60 min**
  **Activity:** Programavimas
  **Comments:** Frontend dalies koregavimas bei atnaujinimas

- **2025-05-07** — *13:00—15:00* — **120 min** 
  **Activity:** PSP veikla, Komandinis darbas
  **Comments:** Klasių diagrama
**STAGE 3**
- **2025-05-28** — *12:00—13:00* — **60 min** 
  **Activity:** Programavimas
  **Comments:** Front-End pakeitimas


### Robert Šatkevič
- **2025-03-26** — *11:00–13:00* — **120 min**  
  **Activity:** Planavimas, PSP veikla  
  **Comments:** UML diagramos, pildoma laiko fiksavimo lentelė  

- **2025-04-05** — *18:00–19:10* — **70 min**  
  **Activity:** Atsiskaitymas  
  **Comments:** Klaidų taisymas: readme, UML diagramų taisymas

- **2025-04-24** — *09:00–11:30* — **150 min** 
  **Activity:** Programavimas
  **Comments:** Backend dalies kodavimas (DAO, service, model)

- **2025-05-07** — *13:00—15:00* — **120 min** 
  **Activity:** PSP veikla, Komandinis darbas
  **Comments:** Klasių diagrama
**STAGE 3**
- **2025-05-27** - *15:00-15:30* - **30 min**
  **Acitivity:** Programavimas
  **Comments:** Exportavimo feature
- **2025-05-27** - *16:00-16:30* - **30 min**
**Acitivity:** Projektavimas, Programavimas
**Comments:** Tobulinimas esamų klasių

### Dominykas Pavlavičius
- **2025-04-25** — *10:00—11:40* — **100 min**
  **Activity:** Kodo peržiūra, Programavimas
  **Comments:** Sujungiau Backend su Frontend

- **2025-05-07** — *13:00—15:00* — **120 min** 
  **Activity:** PSP veikla, Komandinis darbas
  **Comments:** Klasių diagrama
**STAGE 3**
- **2025-05-28** — *18:00—19:00* — **60 min** 
  **Activity:** Programavimas
  **Comments:** Filtrų cpp failai
- **2025-05-29** — *21:00—22:10* — **70 min** 
  **Activity:** Programavimas
  **Comments:** Sujungti filtrai su Front-end