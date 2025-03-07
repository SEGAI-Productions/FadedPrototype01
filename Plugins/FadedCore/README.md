# Faded Core

A core plugin for the Faded game that provides shared functionality across the project.

## Features

- Common gameplay systems
- Shared utilities and helper functions
- Core game types and interfaces

## Usage

This plugin is designed to be used as a dependency for other modules in the Faded game project.

### Adding to a Module

To use FadedCore in another module, add it to your module's dependencies:

```csharp
PublicDependencyModuleNames.AddRange(
    new string[]
    {
        "Core",
        "CoreUObject",
        "Engine",
        "FadedCore"
    }
);
```

### Including Headers

```cpp
#include "FadedCore/Public/YourHeaderFile.h"
```

## Development

To add new functionality to the FadedCore plugin:

1. Add new header files to the `Public` directory for interfaces and classes that should be exposed to other modules
2. Add implementation files to the `Private` directory
3. Update the `FadedCore.Build.cs` file if you need to add new dependencies 