import { Pressable, Text, View } from "react-native";
import { styles } from "../styles/ColorItem";

type ColorItemProps = {
    color: string,
    onPress?: () => void,
    borderWidth: number,
    text?: string
}

export type ColorItemType = {
    color: string,
    id: string
}

function ColorItem({ color, onPress, borderWidth, text }: ColorItemProps) {
    return (
        <Pressable
            onPress={onPress}
        >
            <View style={[styles.container, {backgroundColor: color, borderWidth: borderWidth}]}>
                <Text
                    style={{alignSelf:"center"}}
                >{text}</Text>
            </View>
        </Pressable>
    );
}

export default ColorItem;