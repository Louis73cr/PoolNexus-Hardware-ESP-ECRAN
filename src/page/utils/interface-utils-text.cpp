/* **************************************************************************** */
/*                                                                              */
/*                                                  ::::    :::     ::::::::    */
/*   interface-utils-text.cpp                       :+:+:   :+:    :+:    :+:   */
/*                                                  :+:+:+  +:+    +:+          */
/*   By: marvin <marvin@student.42.fr>              +#+ +:+ +#+    +#++:++#++   */
/*                                                  +#+  +#+#+#           +#+   */
/*   Created: 2025/11/13 23:07:55 by marvin         #+#   #+#+#    #+#    #+#   */
/*   Updated: 2025/11/13 23:07:55 by marvin         ###    ####     ########    */
/*                                                                              */
/* **************************************************************************** */
#include "interface-utils.hpp"

void interfaceUtils::drawText(TextZone* textZone) {
    if (!textZone->isDisplayed) {
        return;
    }
    
    display->setTextSize(textZone->fontSize);
    display->setTextColor(textZone->textColor);
    display->setCursor(textZone->x, textZone->y);
    display->print(textZone->text.c_str());
    display->flush();
}