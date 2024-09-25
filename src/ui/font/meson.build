font_conv_script = find_program('./font_converter.py')
message(font_conv_script.full_path())
# dear meson,
# why do you assume the python you're running with is the same that /usr/bin/env python3 would provide
# sincerely,
# a nix user
font_converter = generator(find_program('python3'),
                           output : '@BASENAME@.c',
                           arguments : [font_conv_script.full_path(), '@INPUT@', '@OUTPUT@', '@BASENAME@'])
sources += font_converter.process('Font_Terminus.png')
