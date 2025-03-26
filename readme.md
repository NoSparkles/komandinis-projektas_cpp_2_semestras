# Finance Manager App

## Team: *Unhandled Exception*

### Authors
| Name               | Role                                      |
|--------------------|-------------------------------------------|
| **Robert Šatkevič** | Backend Developer, Documentation Writer   |
| **Aurimas Vižinis** | Frontend Developer, Documentation Writer  |

---

## Technology Stack

| Layer         | Technology Used      |
|---------------|-----------------------|
| **Frontend**  | C++, QT |
| **Backend**   | C++    |
| **Storage**   | Local File System           |
| **Visualization** | Pie Charts, Tables |
| **Tools**     | QT Creator, Smartdraw, Git/GitHub |

---

## Features Overview

### Use Case Diagram
![Use Case Diagram](./image1.png)

- **User Interactions:**
  - Choose between income or expense view
  - Add new financial entries
  - Save and export data
  - Filter data by value, type, or date
  - Export filtered data as a table or pie chart

---

## Data Flow Overview

### Flowchart Diagram
![Flowchart](./image2.png)

1. **User Input**
2. **Data Validation**
   - Shows **Errors** or proceeds with **Valid Data**
3. **Valid Data** is saved to a **Storage File**
4. Apply **Filters**
   - View as **Table** or **Pie Chart**
5. **Export/Save Data**

---

## Application Flow

### Component Interaction Diagram
![Application Logic](./image3.png)

- The **Application** sends and receives:
  - Entry Data
  - Success/Error responses
  - Filtered list of entries
- **View Controllers** (Add / Main) interact with the **Data Manager**
- The **Data Manager** handles communication with the **Storage File**

---

## Export Formats
- Filtered entries can be exported:
  - As tables
  - As pie charts for visual breakdown

