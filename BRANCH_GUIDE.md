# Branch Management Guide

## Branch Structure

### Upstream PR Branches
- **Purpose**: Clean branches for submitting PRs to vial-kb/vial-qmk
- **Naming**: `pr/keyboard-name` or `feature/description`
- **Example**: `q15-max-clean`
- **Setup**: `~/manage-keymaps.sh upstream`
- **Never includes**: Personal keymaps (d3lilah, delilah, etc.)

### Personal Branch
- **Purpose**: Your personal configurations and keymaps
- **Name**: `personal`
- **Remote**: `myfork/personal`
- **Setup**: `~/manage-keymaps.sh personal`
- **Includes**: All your d3lilah keymaps and custom keyboards

## Quick Commands

### Before Creating a PR
```bash
# 1. Switch to upstream mode
~/manage-keymaps.sh upstream

# 2. Create clean branch
git checkout -b pr/new-keyboard origin/vial

# 3. Check no personal files
git check-personal

# 4. Preview PR
git pr-preview
```

### Working on Personal Keymaps
```bash
# 1. Switch to personal mode
~/manage-keymaps.sh personal

# 2. Switch to personal branch
git checkout personal

# 3. Make changes and commit
git add keyboards/*/keymaps/d3lilah/
git commit -m "Update personal keymap"

# 4. Push to your fork
git push myfork personal
```

## Git Aliases Available
- `git pr-preview` - Show what would be in PR
- `git pr-files` - List files that would be in PR
- `git check-personal` - Check for personal files

## Current Branches
- `vial` - Local working branch (messy OK)
- `personal` - Your personal keymaps (→ myfork/personal)
- `q15-max-clean` - Clean PR #975 for Q15 Max

## Important Files
- `~/manage-keymaps.sh` - Switch between upstream/personal modes
- `.git/info/exclude` - Local ignore rules (managed by script)

## Remember
- NEVER commit personal keymaps to `pr/*` branches
- ALWAYS use `~/manage-keymaps.sh` to switch contexts
- CHECK before pushing PRs with `git check-personal`