# **GitHub Workflow & Development Guide for FADED Prototype**

## **1. Overview**
This document outlines the **branching strategy, collaboration workflow, and best practices** for the FADED Prototype project. The goal is to **enable asynchronous development**, allowing each team member to work independently on their feature without major conflicts.

---

## **2. Repository Structure**
```
/FadedPrototype
  /Content
    /Blueprints
      /CombatSystem
      /CoverSystem
      /CameraSystem
      /CharacterMovement
      /AI
    /Animations
      /Player
      /Enemies
    /Characters
      /Player
      /NPCs
    /Environments
    /UI
```
- Each system (e.g., **Combat, Cover, Camera**) has **its own Blueprint folder**.
- Avoid modifying files outside your area **unless necessary** to prevent merge conflicts.

---

## **3. Branching Strategy**
We follow a **feature-based branching model**:

### **Main Branch (Protected)**
- Holds only **stable, tested features**.
- All changes must go through **Development first**.

### **Development Branch (Staging Branch)**
- Integrates completed features before merging into **Main**.
- Developers sync with this branch **regularly**.

### **Feature Branches (One per system)**
Each developer works on a dedicated **feature branch**, such as:
- `feature/combat-system` → **Combat Designer**
- `feature/cover-system` → **UE Developer 1**
- `feature/camera-system` → **UE Developer 2**
- `feature/character-animation` → **Animators**
- `feature/character-assets` → **3D Character Artist**
- `feature/environment-assets` → **Environment Artist**

**Process:**
1. **Create a branch from `Development`** (e.g., `feature/combat-system`).
2. Work on your feature.
3. When ready, **open a Pull Request (PR) to `Development`**.
4. Another team member **reviews the PR before merging**.

---

## **4. Git Workflow & Best Practices**
### **Daily Workflow**
1. **Pull latest `Development` updates** before starting work:
   ```sh
   git checkout development
   git pull origin development
   ```
2. **Create or switch to your feature branch**:
   ```sh
   git checkout -b feature/your-feature-name
   ```
3. **Commit regularly and push changes**:
   ```sh
   git add .
   git commit -m "Your commit message"
   git push origin feature/your-feature-name
   ```
4. **When ready, open a Pull Request (PR)** targeting `Development`.
5. **Once merged into `Development`, delete your feature branch.**

---

## **5. Merge & Conflict Avoidance Process**
To minimize conflicts:
- **Pull latest changes** from `Development` **before pushing**.
- **Communicate in Discord** if touching shared systems.
- **Review PRs before merging** to avoid breaking the build.

---

## **6. Handling Large Files (No Git LFS)**
Since we are using **free GitHub** and **not Git LFS**, follow these rules:

### **🚫 Do NOT push large binary files to Git**
- Do not commit `.uasset`, `.umap`, or textures/models unless absolutely necessary.
- Add a `.gitignore` file to prevent tracking unnecessary Unreal Engine files:
   ```sh
   *.umap
   *.uasset
   Saved/
   Intermediate/
   DerivedDataCache/
   ```

### **✅ Use Google Drive / Dropbox for Large Assets**
- Store **textures, models, animations, and audio** in a shared cloud drive.
- Example **Google Drive structure**:
  ```
  /FadedPrototype_Assets
    /Characters
    /Environments
    /Animations
    /Textures
  ```
- When an asset is updated, upload it to **Google Drive** and post a link in Discord.

### **✅ Use GitHub Releases for Backups**
- If you need to store **a major milestone**, create a **GitHub Release** and upload a ZIP file of assets.

---

## **7. Collaboration & Communication**
- **Primary tools**: **GitHub & Discord**.
- **Weekly sync meetings** on Discord (as needed).
- **Use GitHub Issues & PR comments** for discussions.
- **Tag relevant team members** in PRs for feedback.

---

## **8. Final Notes**
- **Keep your commits small and logical**.
- **Document any major changes** in PR descriptions.
- **Always test before merging**.
- **If unsure, ask in Discord before making changes to shared systems.**

This workflow ensures smooth **asynchronous development** while keeping integrations efficient. 🚀

