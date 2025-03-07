# Cover System Plugin for Unreal Engine

This plugin adds a cover system to your Unreal Engine project, allowing characters to take cover behind objects in the environment.

## Features

- **Cover Detection**: Automatically detect suitable cover objects in the environment
- **Cover Movement**: Enter, exit, and move between cover positions
- **Cover Actions**: Fire from cover, blind fire, and peek around corners
- **Gameplay Abilities Integration**: Uses the Gameplay Abilities System for cover actions
- **Input Binding**: Easily bind cover actions to input controls
- **Blueprint Support**: Full blueprint support for all cover functionality
- **Animation Integration**: Integrate with animation blueprints for smooth cover animations

## Installation

1. Copy the `CoverSystem` folder to your project's `Plugins` directory
2. Enable the plugin in the Unreal Engine Editor (Edit > Plugins)
3. Restart the editor

## Integration with FadedCharacter

The plugin is designed to work with `AFadedCharacter` out of the box. To add cover functionality to your character:

1. Add the `UFadedCharacterCoverComponent` to your character blueprint
2. Set up the input actions for cover controls
3. Configure the cover abilities in the component properties

## Usage

### Adding Cover to a Character

```cpp
// In your character's constructor
CoverComponent = CreateDefaultSubobject<UFadedCharacterCoverComponent>(TEXT("CoverComponent"));
```

### Setting Up Input

```cpp
// In your character's SetupPlayerInputComponent method
if (CoverComponent)
{
    CoverComponent->SetupPlayerInputComponent(PlayerInputComponent);
}
```

### Using Cover in Gameplay

The cover system provides the following functionality:

- **Enter Cover**: Press the enter cover button when near a suitable object
- **Exit Cover**: Press the exit cover button to leave cover
- **Fire from Cover**: Press the fire button while in cover to lean out and fire
- **Blind Fire**: Press the blind fire button to fire without exposing yourself
- **Move in Cover**: Use movement controls to slide along cover

### Creating Custom Cover Abilities

You can create custom cover abilities by extending the `UCoverGameplayAbility` class:

```cpp
UCLASS()
class MYGAME_API UMyCustomCoverAbility : public UCoverGameplayAbility
{
    GENERATED_BODY()
    
public:
    UMyCustomCoverAbility();
    
    virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
};
```

## Cover Detection

The cover system uses raycasts to detect suitable cover objects. The following criteria are used:

- **Height**: The object must be tall enough to provide cover
- **Angle**: The object must be roughly vertical (not a floor or ceiling)
- **Space**: There must be enough space behind the cover for the character

## Animation Integration

To integrate with your animation blueprint:

1. Create animation montages for entering, exiting, and firing from cover
2. Assign these montages to the corresponding abilities in the cover component
3. Use the cover state in your animation blueprint to blend between animations

## Extending the Plugin

The plugin is designed to be easily extended. You can:

- Create custom cover abilities
- Add new cover actions
- Modify the cover detection algorithm
- Integrate with other systems like weapons or inventory

## License

This plugin is licensed under the MIT License. See the LICENSE file for details.

## Credits

Developed by [Your Name]

## Support

For support, please contact [Your Email] 