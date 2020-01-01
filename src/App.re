let component = ReasonReact.statelessComponent("Component1");

let correctWord = "Every";
let words = [|"Hello", "Every", "World"|];

let handleChange = (event, _self) => Js.log(ReactEvent.Form.target(event)##value);

let filterWords = attemptedWord => Belt.Array.keep(words, word => word != attemptedWord);

let renderWords = wordsArray => 
  Array.map(word => <div>(ReasonReact.string(word))</div>, wordsArray);

let make = (_children) => {
  ...component,
  render: self =>
    <div>
      <div>...(correctWord -> filterWords -> renderWords)</div>
      <input onChange=(self.handle(handleChange)) />
    </div>,
};
