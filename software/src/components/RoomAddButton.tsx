import { Pressable, Text } from "react-native";
import { Colors } from "../constants/Colors";
import { styles } from "../styles/RoomAddButton";

function RoomAddButton() {
    return (
        <Pressable
            style={({ pressed }) => [
                styles.roomAddButton,
                {
                    backgroundColor: pressed ? Colors.applianceCardPressed : "transparent"
                }
            ]}
        >
            <Text style={styles.roomAddText}>+</Text>
        </Pressable>
    )
}

export default RoomAddButton;