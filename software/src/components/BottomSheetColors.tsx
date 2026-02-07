import { Button, View } from "react-native";
import ColorPicker, { ColorFormatsObject, HueSlider, Panel1, Preview } from "reanimated-color-picker";
import { styles } from "../styles/BottomSheetColors";
import ColorList from "./ColorList";
import Separator from "./Separator";

const onSelectColor = ({ hex }: ColorFormatsObject) => {
    setTimeout(() => {
        console.log(hex);
    }, 200)
}



function BottomSheetColors() {
    return (
        <View>
            <View style={styles.colorPickerContainer}>
                <ColorPicker style={styles.colorPicker} value="white" onCompleteJS={onSelectColor}>
                    <Preview hideText={true} disableOpacityTexture={true} hideInitialColor={true} style={{ marginTop: 10, marginBottom: 10, borderRadius: 20, height: 50 }} />
                    <View style={styles.rowContainer}>
                        <HueSlider style={styles.hueSlider} vertical={true} />
                        <Panel1 style={styles.panel} />
                    </View>
                    <Button title="Přidat"></Button>
                </ColorPicker>
            </View>
            <Separator />
            <ColorList enableScroll={true} width={320} marginBottom={0} />
            <Separator />
        </View>
    )
}

export default BottomSheetColors;